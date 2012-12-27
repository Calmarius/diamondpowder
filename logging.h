#define CRYSTAL_EDITOR_MOUSE_MOVE 0
#define REFRACTION_LOG 0
#define RENDERING_LOG 0
#define CRYSTAL_BUCKETING_LOG 0
#define RAYCASTING_LOG 1


#if defined(NDEBUG) || defined(NO_LOG)
    #define log_var(type, x)
#else
    #define log_var(type, x) if (type) log_var_impl(#x, x);
#endif
void log_var_impl(const char *msg, const int &x);
void log_var_impl(const char *msg, const double &x);
void log_var_impl(const char *msg, const Vector3 &x);
void log_var_impl(const char *msg, const Matrix &m);

void log_printf(bool logType, const char *format, ...);

