#include "OpenGLWrapper.h"

#include "Utilities/i18n.h"

#include <stdexcept>

#if defined(SFML_SYSTEM_WINDOWS)

    #include <GL/WGL.h>
    #define glGetProcAddress(a) wglGetProcAddress(a)

#elif defined(SFML_SYSTEM_LINUX) || defined(SFML_SYSTEM_FREEBSD)

    #include <GL/glx.h>
    #define glGetProcAddress(a) glXGetProcAddress((const unsigned char*)a)

#elif defined(SFML_SYSTEM_MACOS)

    #include <OpenGL/glx.h>
    #define glGetProcAddress(a) glXGetProcAddress((const unsigned char*)a)

#endif

#define D_NOT_SUP_ERR _("The following is not supported by your way too old graphics card or drivers:")

GLAPI void APIENTRY glDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices)
{
    static PFNGLDRAWELEMENTSPROC proc = (PFNGLDRAWELEMENTSPROC)glGetProcAddress("glDrawElements");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "OpenGL Vertex Arrays"); }

    return proc(mode, count, type, indices);
}

GLAPI void APIENTRY glActiveTexture (GLenum texture)
{
    static PFNGLACTIVETEXTUREPROC proc = (PFNGLACTIVETEXTUREPROC)glGetProcAddress("glActiveTexture");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "OpenGL Multitexturing"); }

    return proc(texture);
}

GLAPI void APIENTRY glCompileShader (GLuint shader)
{
    static PFNGLCOMPILESHADERPROC proc = (PFNGLCOMPILESHADERPROC)glGetProcAddress("glCompileShader");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "Modern OpenGL Shaders"); }

    return proc(shader);
}

GLAPI void APIENTRY glShaderSource (GLuint shader, GLsizei count, const GLchar* *string, const GLint *length)
{
    static PFNGLSHADERSOURCEPROC proc = (PFNGLSHADERSOURCEPROC)glGetProcAddress("glShaderSource");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "Modern OpenGL Shaders"); }

    return proc(shader, count, string, length);
}

GLAPI void APIENTRY glGetShaderInfoLog (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
{
    static PFNGLGETSHADERINFOLOGPROC proc = (PFNGLGETSHADERINFOLOGPROC)glGetProcAddress("glGetShaderInfoLog");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "Modern OpenGL Shaders"); }

    return proc(shader, bufSize, length, infoLog);
}

GLAPI void APIENTRY glGetShaderiv (GLuint shader, GLenum pname, GLint *params)
{
    static PFNGLGETSHADERIVPROC proc = (PFNGLGETSHADERIVPROC)glGetProcAddress("glGetShaderiv");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "Modern OpenGL Shaders"); }

    return proc(shader, pname, params);
}

GLAPI GLuint APIENTRY glCreateShader (GLenum type)
{
    static PFNGLCREATESHADERPROC proc = (PFNGLCREATESHADERPROC)glGetProcAddress("glCreateShader");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "Modern OpenGL Shaders"); }

    return proc(type);
}

GLAPI void APIENTRY glDeleteShader (GLuint shader)
{
    static PFNGLDELETESHADERPROC proc = (PFNGLDELETESHADERPROC)glGetProcAddress("glDeleteShader");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "Modern OpenGL Shaders"); }

    return proc(shader);
}

GLAPI void APIENTRY glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source)
{
    static PFNGLGETSHADERSOURCEPROC proc = (PFNGLGETSHADERSOURCEPROC)glGetProcAddress("glGetShaderSource");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "Modern OpenGL Shaders"); }

    return proc(shader, bufSize, length, source);
}

GLAPI GLuint APIENTRY glCreateProgram()
{
    static PFNGLCREATEPROGRAMPROC proc = (PFNGLCREATEPROGRAMPROC)glGetProcAddress("glCreateProgram");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "Modern OpenGL Shaders"); }

    return proc();
}

GLAPI void APIENTRY glDeleteProgram (GLuint program)
{
    static PFNGLDELETEPROGRAMPROC proc = (PFNGLDELETEPROGRAMPROC)glGetProcAddress("glDeleteProgram");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "Modern OpenGL Shaders"); }

    return proc(program);
}

GLAPI void APIENTRY glAttachShader(GLuint program, GLuint shader)
{
    static PFNGLATTACHSHADERPROC proc = (PFNGLATTACHSHADERPROC)glGetProcAddress("glAttachShader");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "Modern OpenGL Shaders"); }

    return proc(program, shader);
}

GLAPI void APIENTRY glLinkProgram(GLuint program)
{
    static PFNGLLINKPROGRAMPROC proc = (PFNGLLINKPROGRAMPROC)glGetProcAddress("glLinkProgram");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "Modern OpenGL Shaders"); }

    return proc(program);
}

GLAPI void APIENTRY glUseProgram(GLuint program)
{
	static PFNGLUSEPROGRAMPROC proc = (PFNGLUSEPROGRAMPROC)glGetProcAddress("glUseProgram");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "Modern OpenGL Shaders"); }

	proc(program);
}

GLAPI void APIENTRY glGetProgramInfoLog (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
{
    static PFNGLGETPROGRAMINFOLOGPROC proc = (PFNGLGETPROGRAMINFOLOGPROC)glGetProcAddress("glGetProgramInfoLog");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "Modern OpenGL Shaders"); }

    return proc(shader, bufSize, length, infoLog);
}

GLAPI void APIENTRY glGetProgramiv (GLuint shader, GLenum pname, GLint *params)
{
    static PFNGLGETPROGRAMIVPROC proc = (PFNGLGETPROGRAMIVPROC)glGetProcAddress("glGetProgramiv");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "Modern OpenGL Shaders"); }

    return proc(shader, pname, params);
}

GLAPI void APIENTRY glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
{
    static PFNGLGETACTIVEATTRIBPROC proc = (PFNGLGETACTIVEATTRIBPROC)glGetProcAddress("glGetActiveAttrib");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "Modern OpenGL Shaders"); }

    return proc(program, index, bufSize, length, size, type, name);
}

GLAPI void APIENTRY glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
{
    static PFNGLGETACTIVEUNIFORMPROC proc = (PFNGLGETACTIVEUNIFORMPROC)glGetProcAddress("glGetActiveUniform");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "Modern OpenGL Shaders"); }

    return proc(program, index, bufSize, length, size, type, name);
}

GLAPI GLint APIENTRY glGetAttribLocation (GLuint program, const GLchar *name)
{
    static PFNGLGETATTRIBLOCATIONPROC proc = (PFNGLGETATTRIBLOCATIONPROC)glGetProcAddress("glGetAttribLocation");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "Modern OpenGL Shaders"); }

    return proc(program, name);
}

GLAPI GLint APIENTRY glGetUniformLocation (GLuint program, const GLchar *name)
{
    static PFNGLGETUNIFORMLOCATIONPROC proc = (PFNGLGETUNIFORMLOCATIONPROC)glGetProcAddress("glGetUniformLocation");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "Modern OpenGL Shaders"); }

    return proc(program, name);
}

GLAPI const GLubyte * APIENTRY glGetStringi (GLenum name, GLuint index)
{
    static PFNGLGETSTRINGIPROC proc = (PFNGLGETSTRINGIPROC)glGetProcAddress("glGetStringi");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "OpenGL 3"); }

    return proc(name, index);
}

GLAPI void APIENTRY glBindFragDataLocation(GLuint program, GLuint color, const GLchar* name)
{
    static PFNGLBINDFRAGDATALOCATIONPROC proc = (PFNGLBINDFRAGDATALOCATIONPROC)glGetProcAddress("glBindFragDataLocation");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "Modern OpenGL Shaders"); }

    return proc(program, color, name);
}

GLAPI void APIENTRY glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer)
{
    static PFNGLVERTEXATTRIBPOINTERPROC proc = (PFNGLVERTEXATTRIBPOINTERPROC)glGetProcAddress("glVertexAttribPointer");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "Modern OpenGL Shaders"); }

    return proc(index, size, type, normalized, stride, pointer);
}

GLAPI void APIENTRY glBindBuffer(GLenum target, GLuint buffer)
{
    static PFNGLBINDBUFFERPROC proc = (PFNGLBINDBUFFERPROC)glGetProcAddress("glBindBuffer");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "OpenGL Vertex Array Objects"); }

    return proc(target, buffer);
}

GLAPI void APIENTRY glEnableVertexAttribArray(GLuint index)
{
    static PFNGLENABLEVERTEXATTRIBARRAYPROC proc = (PFNGLENABLEVERTEXATTRIBARRAYPROC)glGetProcAddress("glEnableVertexAttribArray");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "OpenGL Vertex Array Objects"); }

    return proc(index);
}

GLAPI void APIENTRY glDisableVertexAttribArray(GLuint index)
{
    static PFNGLDISABLEVERTEXATTRIBARRAYPROC proc = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)glGetProcAddress("glDisableVertexAttribArray");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "OpenGL Vertex Array Objects"); }

    return proc(index);
}

GLAPI void APIENTRY glUniform1i(GLint location, GLint v0)
{
    static PFNGLUNIFORM1IPROC proc = (PFNGLUNIFORM1IPROC)glGetProcAddress("glUniform1i");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "Modern OpenGL Shaders"); }

    return proc(location, v0);
}

GLAPI void APIENTRY glUniform4fv(GLint location, GLsizei count, const GLfloat* value)
{
    static PFNGLUNIFORM4FVPROC proc = (PFNGLUNIFORM4FVPROC)glGetProcAddress("glUniform4fv");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "Modern OpenGL Shaders"); }

    return proc(location, count, value);
}

GLAPI void APIENTRY glUniform3fv(GLint location, GLsizei count, const GLfloat* value)
{
    static PFNGLUNIFORM3FVPROC proc = (PFNGLUNIFORM3FVPROC)glGetProcAddress("glUniform3fv");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "Modern OpenGL Shaders"); }

    return proc(location, count, value);
}

GLAPI void APIENTRY glUniform2fv(GLint location, GLsizei count, const GLfloat* value)
{
    static PFNGLUNIFORM2FVPROC proc = (PFNGLUNIFORM2FVPROC)glGetProcAddress("glUniform2fv");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "Modern OpenGL Shaders"); }

    return proc(location, count, value);
}

GLAPI void APIENTRY glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
    static PFNGLUNIFORMMATRIX4FVPROC proc = (PFNGLUNIFORMMATRIX4FVPROC)glGetProcAddress("glUniformMatrix4fv");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "Modern OpenGL Shaders"); }

    return proc(location, count, transpose, value);
}

GLAPI void APIENTRY glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
    static PFNGLUNIFORMMATRIX3FVPROC proc = (PFNGLUNIFORMMATRIX3FVPROC)glGetProcAddress("glUniformMatrix3fv");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "Modern OpenGL Shaders"); }

    return proc(location, count, transpose, value);
}
/*
GLAPI void APIENTRY glBindBuffer(GLenum target, GLuint buffer)
{
    PFNGLBINDBUFFERPROC proc = (PFNGLBINDBUFFERPROC)glGetProcAddress("glBindBuffer");
    return proc(target, buffer);
}
*/
GLAPI void APIENTRY glDeleteBuffers(GLsizei n, const GLuint *buffers)
{
    static PFNGLDELETEBUFFERSPROC proc = (PFNGLDELETEBUFFERSPROC)glGetProcAddress("glDeleteBuffers");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "OpenGL Vertex Array Objects"); }

    return proc(n, buffers);
}

GLAPI void APIENTRY glGenBuffers(GLsizei n, GLuint *buffers)
{
    static PFNGLGENBUFFERSPROC proc = (PFNGLGENBUFFERSPROC)glGetProcAddress("glGenBuffers");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "OpenGL Vertex Array Objects"); }

    return proc(n, buffers);
}

GLAPI void APIENTRY glBufferData (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage)
{
    static PFNGLBUFFERDATAPROC proc = (PFNGLBUFFERDATAPROC)glGetProcAddress("glBufferData");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "OpenGL Vertex Array Objects"); }

    return proc(target, size, data, usage);
}

GLAPI void APIENTRY glBindVertexArray(GLuint arr)
{
    static PFNGLBINDVERTEXARRAYPROC proc = (PFNGLBINDVERTEXARRAYPROC)glGetProcAddress("glBindVertexArray");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "OpenGL Vertex Array Objects"); }

    return proc(arr);
}

GLAPI void APIENTRY glDeleteVertexArrays(GLsizei n, const GLuint *arrays)
{
    static PFNGLDELETEVERTEXARRAYSPROC proc = (PFNGLDELETEVERTEXARRAYSPROC)glGetProcAddress("glDeleteVertexArrays");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "OpenGL Vertex Array Objects"); }

    return proc(n, arrays);
}

GLAPI void APIENTRY glGenVertexArrays(GLsizei n, GLuint *arrays)
{
    static PFNGLGENVERTEXARRAYSPROC proc = (PFNGLGENVERTEXARRAYSPROC)glGetProcAddress("glGenVertexArrays");
    if(!proc) { throw std::runtime_error(D_NOT_SUP_ERR + "OpenGL Vertex Array Objects"); }

    return proc(n, arrays);
}
