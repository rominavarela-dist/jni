public class JNIMath {
    static {
       System.loadLibrary("math"); // Load native library at runtime
    }

    // Declare a native methods
    public native int pow2(int a);
    public native boolean isNegative(boolean bool);
    public native String copyString(String text);
    public native int sumAll(int[] intArray);

    // Test Driver
    public static void main(String[] args) {
       JNIMath math= new JNIMath();
       System.out.println(math.pow2(2));
       System.out.println(math.isNegative(true));
       System.out.println(math.copyString("hola"));
       System.out.println(math.sumAll(new int[]{1,2,3,4,5}));
    }
}
