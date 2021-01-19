using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace NetPrograssTrackerExtension {
    [NetPT.Progress(50), NetPT.ProgressCategory("SaveMethods"), NetPT.ProgressDescription("Creates a webhook so you can easily run it before building")]
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

        private string HashHMAC_SHA256(string message) {
            var hash = new HMACSHA256(Secret.StringEncode());
            return hash.ComputeHash(message.StringEncode()).HashEncode();
        }
    }
}
