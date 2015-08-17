public class MPIController {
    static {
       System.loadLibrary("mpimaster"); // Load native library at runtime
                                   // hello.dll (Windows) or libhello.so (Unixes)

        loadGlobalLibraries();

        if(!loadGlobalLibraries())
        {
            System.out.println("JAVA BINDINGS FAILED TO LOAD REQUIRED LIBRARIES");
            System.exit(1);
        }
    }

    private static native boolean loadGlobalLibraries();
    private native void init();
    private native void sayHello();
    private native void finish();

    // Test Driver
    public static void main(String[] args) {
       MPIController ctrl = new MPIController();
       ctrl.init();
       for(int i=0; i<10; i++)
        {
            System.out.println("(iteration "+i+")");
            ctrl.sayHello();
        }
       ctrl.finish();
    }
}
