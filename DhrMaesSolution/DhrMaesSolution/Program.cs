using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NetPrograssTrackerExtension;

namespace DhrMaesSolution {
    public class Program {
        public static void Main(string[] args) {
            Webhook hook = new Webhook("https://www.dhrmaes.com/CosmicCloud/Progress.php", "gRp33EXs3aNY4a2bePv9feev6qsUZPCdF44U2HPZWWK7TNJWqBndAxumkGVJ2QgHWZsKWDvYw6qCnP3xtkqBtzJUFnEDh2LdrUNrYsn9eWPZKW6zuVPA7DGxQg59UHuY");
            Console.WriteLine(Webhook.GetPublicIP());
        }
    }
}
