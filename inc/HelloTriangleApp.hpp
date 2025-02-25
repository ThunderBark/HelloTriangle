class HelloTriangleApp {
public:
    HelloTriangleApp( );
    ~HelloTriangleApp( );

    void run( ) {
        initWindow( );
        initVulkan( );
        mainLoop( );
        cleanup( );
    }

private:
    void initWindow( );

    void createInstance( );

    void initVulkan( );

    void mainLoop( );

    void cleanup( );

private:
    struct ctx_t* ctx;
};