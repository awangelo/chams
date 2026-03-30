#include "pch.h"
#include "chams.h"

namespace Features
{
    VOID
    ApplyChams(GLfloat x, GLfloat y, GLfloat z)
    {
        if (x == 0.9375f && y == 0.9375f && z == 0.9375f) {
            glEnable(GL_POLYGON_OFFSET_FILL);
            glPolygonOffset(1.0f, -2000000.0f); 
            glDisable(GL_TEXTURE_2D);
            glDisable(GL_LIGHTING);
            glColor3f(1.0f, 0.0f, 0.0f);
        }
    }

    VOID
    RestoreChams(GLfloat x, GLfloat y, GLfloat z)
    {
        if (x != 0.9375f && y != 0.9375f && z != 0.9375f) {
            glEnable(GL_TEXTURE_2D);
        }
    }
}
