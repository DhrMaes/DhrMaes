using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Http;
using System.Net.Http.Headers;
using NetPrograssTrackerExtension;

namespace DhrMaesSolution {
    public class Program {
        public static void Main(string[] args) {
            var test = Main_test();
            test.Wait();

            Console.ReadKey(true);

            //Webhook hook = new Webhook("https://www.dhrmaes.com/CosmicCloud/Progress.php", "gRp33EXs3aNY4a2bePv9feev6qsUZPCdF44U2HPZWWK7TNJWqBndAxumkGVJ2QgHWZsKWDvYw6qCnP3xtkqBtzJUFnEDh2LdrUNrYsn9eWPZKW6zuVPA7DGxQg59UHuY");
            //Console.WriteLine(Webhook.GetPublicIP());
        }

        public static async Task Main_test() {
            using (var httpClient = new HttpClient()) {
                using (var request = new HttpRequestMessage(new HttpMethod("POST"), "http://dhrmaes.ddns.net:2000/assets/php/AddPoint.php")) {
                    request.Content = new StringContent("{\"latitude\": 5119.662109375,\"longitude\": 313.0767822265625,\"pm10\": 125,\"pm25\": 150}");
                    request.Content.Headers.ContentType = MediaTypeHeaderValue.Parse("application/json");

                    var response = await httpClient.SendAsync(request);
                    if (response.IsSuccessStatusCode) {
                        string textresponse = await response.Content.ReadAsStringAsync();
                        Console.WriteLine(textresponse);
                    } else {
                        string textresponse = await response.Content.ReadAsStringAsync();
                        Console.WriteLine(textresponse);
                    }
                }
            }
        }
    }
}
