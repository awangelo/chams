#include "pch.h"
#include <gl/GL.h>
#include <cstdio>
#include "Features/chams.h"

typedef VOID (WINAPI* glTranslatef_t)(GLfloat x, GLfloat y, GLfloat z);
typedef VOID (WINAPI* glScalef_t)(GLfloat x, GLfloat y, GLfloat z);
typedef VOID (WINAPI* glOrtho_t)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);

glTranslatef_t o_glTranslatef = NULL;
glScalef_t o_glScalef = NULL;
glOrtho_t o_glOrtho = NULL;

static VOID WINAPI
hk_glTranslatef(GLfloat x, GLfloat y, GLfloat z)
{
    //
    o_glTranslatef(x, y, z);
}

static VOID WINAPI
hk_glScalef(GLfloat x, GLfloat y, GLfloat z)
{
    Features::ApplyChams(x, y, z);
    o_glScalef(x, y, z);
    Features::RestoreChams(x, y, z);
}

static VOID WINAPI
hk_glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar)
{
    //
    o_glOrtho(left, right, bottom, top, zNear, zFar);
}

BOOL
InitializeHooks(VOID)
{
    MH_STATUS status = MH_Initialize();
    if (status != MH_OK) {
        printf("  [-] Failed to initialize MinHook: %s\n", MH_StatusToString(status));
        return FALSE;
    }
    printf("  [+] MinHook initialized successfully.\n");

    status = MH_CreateHookApi(L"opengl32.dll", "glTranslatef", &hk_glTranslatef, reinterpret_cast<LPVOID*>(&o_glTranslatef));
    if (status != MH_OK) {
        printf("  [-] Failed to create hook for glTranslatef: %s\n", MH_StatusToString(status));
        return FALSE;
    }
    printf("  [+] Hook for glTranslatef created successfully.\n");

    status = MH_CreateHookApi(L"opengl32.dll", "glScalef", &hk_glScalef, reinterpret_cast<LPVOID*>(&o_glScalef));
    if (status != MH_OK) {
        printf("  [-] Failed to create hook for glScalef: %s\n", MH_StatusToString(status));
        return FALSE;
    }
    printf("  [+] Hook for glScalef created successfully.\n");

    status = MH_CreateHookApi(L"opengl32.dll", "glOrtho", &hk_glOrtho, reinterpret_cast<LPVOID*>(&o_glOrtho));
    if (status != MH_OK) {
        printf("  [-] Failed to create hook for glOrtho: %s\n", MH_StatusToString(status));
        return FALSE;
    }
    printf("  [+] Hook for glOrtho created successfully.\n");

    status = MH_EnableHook(MH_ALL_HOOKS);
    if (status != MH_OK) {
        printf("  [-] Failed to enable hooks: %s\n", MH_StatusToString(status));
    }
    printf("  [+] All hooks enabled.\n");

    return TRUE;
}
