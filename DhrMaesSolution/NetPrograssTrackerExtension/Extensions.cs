using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Globalization;
using System.Threading.Tasks;

namespace NetPrograssTrackerExtension {
    public static class Extensions {
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
