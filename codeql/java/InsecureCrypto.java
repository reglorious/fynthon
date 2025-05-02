import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;
import java.security.MessageDigest;
import java.util.Base64;

/**
 * InsecureCrypto demonstrates insecure uses of:
 *  1. Triple DES (DESede) in ECB mode with PKCS5Padding
 *  2. MD5 hashing
 *
 * Warning: Both Triple DES/ECB and MD5 are broken and MUST NOT be used in production.
 */
public class InsecureCrypto {

    // —— Triple DES (DESede) Settings —— 
    // Algorithm/mode/padding
    private static final String TRIPLE_DES_ALGORITHM = "DESede/ECB/PKCS5Padding";
    // 24-byte key (168-bit with parity bits); insecure to hard-code!
    private static final byte[] TRIPLE_DES_KEY = "0123456789ABCDEFGHJKLMNP".getBytes();

    // —— MD5 Settings —— 
    private static final String MD5_ALGORITHM = "MD5";

    /**
     * Encrypts the given plaintext using Triple DES in ECB mode.
     *
     * @param plaintext the text to encrypt
     * @return Base64-encoded ciphertext
     * @throws Exception on any cryptographic error
     */
    public static String encrypt3DES(String plaintext) throws Exception {
        Cipher cipher = Cipher.getInstance(TRIPLE_DES_ALGORITHM);
        SecretKeySpec keySpec = new SecretKeySpec(TRIPLE_DES_KEY, "DESede");
        cipher.init(Cipher.ENCRYPT_MODE, keySpec);
        byte[] encrypted = cipher.doFinal(plaintext.getBytes("UTF-8"));
        return Base64.getEncoder().encodeToString(encrypted);
    }

    /**
     * Decrypts the given Base64-encoded ciphertext using Triple DES in ECB mode.
     *
     * @param base64Ciphertext Base64-encoded ciphertext
     * @return the decrypted plaintext
     * @throws Exception on any cryptographic error
     */
    public static String decrypt3DES(String base64Ciphertext) throws Exception {
        Cipher cipher = Cipher.getInstance(TRIPLE_DES_ALGORITHM);
        SecretKeySpec keySpec = new SecretKeySpec(TRIPLE_DES_KEY, "DESede");
        cipher.init(Cipher.DECRYPT_MODE, keySpec);
        byte[] decoded = Base64.getDecoder().decode(base64Ciphertext);
        byte[] decrypted = cipher.doFinal(decoded);
        return new String(decrypted, "UTF-8");
    }

    /**
     * Computes the MD5 hash of the given input string.
     *
     * @param input the text to hash
     * @return lowercase hex-encoded MD5 digest
     * @throws Exception on any cryptographic error
     */
    public static String md5Hash(String input) throws Exception {
        MessageDigest md = MessageDigest.getInstance(MD5_ALGORITHM);
        byte[] digest = md.digest(input.getBytes("UTF-8"));
        StringBuilder sb = new StringBuilder(digest.length * 2);
        for (byte b : digest) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    // Example usage
    public static void main(String[] args) {
        try {
            String original = "SensitiveData123";
            System.out.println("Original: " + original);

            // Triple DES
            String encrypted = encrypt3DES(original);
            System.out.println("Encrypted (3DES): " + encrypted);
            System.out.println("Decrypted (3DES): " + decrypt3DES(encrypted));

            // MD5
            String md5 = md5Hash(original);
            System.out.println("MD5 Hash: " + md5);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

