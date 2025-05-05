using System;
using System.Security.Cryptography;
using System.Text;

namespace InsecureSample
{
    public class CryptoHelper
    {
        // — Hard-coded Secrets — 
        private const string ApiKey   = "12345-ABCDE";   // CWE-330: Hard-coded credentials :contentReference[oaicite:0]{index=0}
        private const string Password = "P@ssw0rd!";     // CWE-259: Use of hard-coded password :contentReference[oaicite:1]{index=1}

        // — Predictable Randomness —
        private static readonly Random InsecureRandom = new Random(12345); // CWE-330: Insecure randomness :contentReference[oaicite:2]{index=2}

        /// <summary>
        /// Computes MD5 hash (insecure, collision-prone).
        /// </summary>
        public static string ComputeMd5(string input)
        {
            using (var md5 = MD5.Create()) // Underlying MD5CryptoServiceProvider :contentReference[oaicite:3]{index=3}
            {
                byte[] data = md5.ComputeHash(Encoding.UTF8.GetBytes(input)); // Insecure hash function :contentReference[oaicite:4]{index=4}
                var sb = new StringBuilder();
                foreach (var b in data)
                    sb.Append(b.ToString("x2"));
                return sb.ToString();
            }
        }

        /// <summary>
        /// Encrypts data with DES in ECB mode (insecure, small block size & pattern leakage).
        /// </summary>
        public static string EncryptDesEcb(string plaintext)
        {
            byte[] key = Encoding.UTF8.GetBytes("ABCDEFGH"); // 8-byte hard-coded key :contentReference[oaicite:5]{index=5}
            using (var des = DES.Create())
            {
                des.Mode    = CipherMode.ECB;      // ECB mode is insecure :contentReference[oaicite:6]{index=6}
                des.Key     = key;
                des.Padding = PaddingMode.PKCS7;
                var encryptor = des.CreateEncryptor();
                byte[] input  = Encoding.UTF8.GetBytes(plaintext);
                byte[] result = encryptor.TransformFinalBlock(input, 0, input.Length);
                return Convert.ToBase64String(result);
            }
        }

        public static void Main()
        {
            Console.WriteLine("API Key: " + ApiKey);
            Console.WriteLine("Password: " + Password);

            string hash   = ComputeMd5("TestData");         // Triggers MD5 detection :contentReference[oaicite:7]{index=7}
            Console.WriteLine("MD5 Hash: " + hash);

            string cipher = EncryptDesEcb("SecretData");    // Triggers DES/ECB detection :contentReference[oaicite:8]{index=8}
            Console.WriteLine("DES/ECB Cipher: " + cipher);

            int randValue = InsecureRandom.Next();          // Triggers insecure RNG detection :contentReference[oaicite:9]{index=9}
            Console.WriteLine("Insecure Random Value: " + randValue);
        }
    }
}
