#ifndef EGL11EXT_H_INCLUDED
#define EGL11EXT_H_INCLUDED


/*typedef GLboolean (GL_APIENTRYP PFNGLISRENDERBUFFEROESPROC) (GLuint renderbuffer);
typedef void (GL_APIENTRYP PFNGLBINDRENDERBUFFEROESPROC) (GLenum target, GLuint renderbuffer);
typedef void (GL_APIENTRYP PFNGLDELETERENDERBUFFERSOESPROC) (GLsizei n, const GLuint* renderbuffers);
typedef void (GL_APIENTRYP PFNGLGENRENDERBUFFERSOESPROC) (GLsizei n, GLuint* renderbuffers);
typedef void (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEOESPROC) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GL_APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVOESPROC) (GLenum target, GLenum pname, GLint* params);
typedef GLboolean (GL_APIENTRYP PFNGLISFRAMEBUFFEROESPROC) (GLuint framebuffer);
typedef void (GL_APIENTRYP PFNGLBINDFRAMEBUFFEROESPROC) (GLenum target, GLuint framebuffer);
typedef void (GL_APIENTRYP PFNGLDELETEFRAMEBUFFERSOESPROC) (GLsizei n, const GLuint* framebuffers);
typedef void (GL_APIENTRYP PFNGLGENFRAMEBUFFERSOESPROC) (GLsizei n, GLuint* framebuffers);
typedef GLenum (GL_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSOESPROC) (GLenum target);
typedef void (GL_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFEROESPROC) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DOESPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (GL_APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVOESPROC) (GLenum target, GLenum attachment, GLenum pname, GLint* params);
typedef void (GL_APIENTRYP PFNGLGENERATEMIPMAPOESPROC) (GLenum target);
typedef void (GL_APIENTRYP PFNGLWAITFORASYNCCOMMANDCOMPLETIONPROC) ();*/


extern PFNGLISRENDERBUFFEROESPROC glIsRenderbufferOES;
extern PFNGLGENFRAMEBUFFERSOESPROC glGenFramebuffersOES;
extern PFNGLCHECKFRAMEBUFFERSTATUSOESPROC glCheckFramebufferStatusOES;
extern PFNGLBINDFRAMEBUFFEROESPROC glBindFramebufferOES;
extern PFNGLFRAMEBUFFERTEXTURE2DOESPROC glFramebufferTexture2DOES;
extern PFNGLDELETEFRAMEBUFFERSOESPROC glDeleteFramebuffersOES;
/*GL_API void GL_APIENTRY glBindRenderbufferOES (GLenum target, GLuint renderbuffer);
GL_API void GL_APIENTRY glDeleteRenderbuffersOES (GLsizei n, const GLuint* renderbuffers);
GL_API void GL_APIENTRY glGenRenderbuffersOES (GLsizei n, GLuint* renderbuffers);
GL_API void GL_APIENTRY glRenderbufferStorageOES (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
GL_API void GL_APIENTRY glGetRenderbufferParameterivOES (GLenum target, GLenum pname, GLint* params);
GL_API GLboolean GL_APIENTRY glIsFramebufferOES (GLuint framebuffer);
GL_API void GL_APIENTRY glBindFramebufferOES (GLenum target, GLuint framebuffer);
GL_API void GL_APIENTRY glDeleteFramebuffersOES (GLsizei n, const GLuint* framebuffers);
GL_API void GL_APIENTRY glGenFramebuffersOES (GLsizei n, GLuint* framebuffers);
GL_API GLenum GL_APIENTRY glCheckFramebufferStatusOES (GLenum target);
GL_API void GL_APIENTRY glFramebufferRenderbufferOES (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GL_API void GL_APIENTRY glFramebufferTexture2DOES (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_API void GL_APIENTRY glGetFramebufferAttachmentParameterivOES (GLenum target, GLenum attachment, GLenum pname, GLint* params);
GL_API void GL_APIENTRY glGenerateMipmapOES (GLenum target);
*/

#endif