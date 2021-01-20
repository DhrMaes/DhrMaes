using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace NetPrograssTrackerExtension {
    [NetPT.Progress(100), NetPT.ProgressCategory("SaveMethods"), NetPT.ProgressDescription("Creates a webhook so you can easily run it before building")]
    public class Webhook {
        public string Endpoint { get; private set; }
        private string Secret = "";

        public Webhook(string endpoint, string secret) {
            Endpoint = endpoint;
            Secret = secret;
        }

        [NetPT.Progress(100)]
        public async Task ExecuteWebhookAsync(string body) {
            using (var httpClient = new HttpClient()) {
                using (var request = new HttpRequestMessage(new HttpMethod("POST"), Endpoint)) {
                    request.Content = new StringContent(body);
                    request.Content.Headers.ContentType = MediaTypeHeaderValue.Parse("application/json");

                    using (HMACSHA256 hmac = new HMACSHA256(Secret.StringEncode()))
                        request.Headers.Add("HMAC_SHA256", "sha256=" + HashHMAC_SHA256(body));

                    var response = await httpClient.SendAsync(request);
                    if (!response.IsSuccessStatusCode) {
                        string textresponse = await response.Content.ReadAsStringAsync();
                        throw new HttpRequestException(textresponse);
                    }
                }
            }
        }

        public static string GetPublicIP() {
            string url = "http://checkip.dyndns.org";
            System.Net.WebRequest req = System.Net.WebRequest.Create(url);
            System.Net.WebResponse resp = req.GetResponse();
            System.IO.StreamReader sr = new System.IO.StreamReader(resp.GetResponseStream());
            string response = sr.ReadToEnd().Trim();
            string[] a = response.Split(':');
            string a2 = a[1].Substring(1);
            string[] a3 = a2.Split('<');
            string a4 = a3[0];
            return a4;
        }

        private string HashHMAC_SHA256(string message) {
            var hash = new HMACSHA256(Secret.StringEncode());
            return hash.ComputeHash(message.StringEncode()).HashEncode();
        }
    }

    public static class WebhookExtensions {
        public static byte[] StringEncode(this string text) {
            var encoding = new ASCIIEncoding();
            return encoding.GetBytes(text);
        }

        public static string HashEncode(this byte[] hash) {
            return BitConverter.ToString(hash).Replace("-", "").ToLower();
        }

        public static byte[] HexDecode(this string hex) {
            var bytes = new byte[hex.Length / 2];
            for (int i = 0; i < bytes.Length; i++) {
                bytes[i] = byte.Parse(hex.Substring(i * 2, 2), NumberStyles.HexNumber);
            }
            return bytes;
        }
    }
}
