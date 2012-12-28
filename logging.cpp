/*
Copyright (c) 2012, Dávid Csirmaz
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**
 * @file logging.cpp
 *
 * Logging stuff goes here.
 */

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
