#if defined(NDEBUG) || defined(NO_LOG)

void log_printf(bool logType, const char *format, ...) {}
void log_var_impl(const char *msg, const int &x) {}
void log_var_impl(const char *msg, const double &x) {}
void log_var_impl(const char *msg, const Vector3 &x) {}
void log_var_impl(const char *msg, const Matrix &m) {}


#else

void log_printf(bool logType, const char *format, ...)
{
    va_list list;

    if (!logType) return;
    va_start(list, format);
    vprintf(format, list);
    fflush(stdout);
}

void log_var_impl(const char *msg, const int &x)
{
    printf("%s: %d\n", msg, x);
    fflush(stdout);
}

void log_var_impl(const char *msg, const double &x)
{
    printf("%s: %f\n", msg, x);
    fflush(stdout);
}

void log_var_impl(const char *msg, const Vector3 &v)
{
    printf("%s: [%f, %f, %f]\n", msg, v.x, v.y, v.z);
    fflush(stdout);
}

void log_var_impl(const char *msg, const Matrix &m)
{
    printf("%s: \n", msg);
    printf("\t [%10.3f %10.3f %10.3f %10.3f] \n", m.elem[0][0], m.elem[0][1], m.elem[0][2], m.elem[0][3]);
    printf("\t [%10.3f %10.3f %10.3f %10.3f] \n", m.elem[1][0], m.elem[1][1], m.elem[1][2], m.elem[1][3]);
    printf("\t [%10.3f %10.3f %10.3f %10.3f] \n", m.elem[2][0], m.elem[2][1], m.elem[2][2], m.elem[2][3]);
    printf("\t [%10.3f %10.3f %10.3f %10.3f] \n", m.elem[3][0], m.elem[3][1], m.elem[3][2], m.elem[3][3]);
    fflush(stdout);
}


#endif
