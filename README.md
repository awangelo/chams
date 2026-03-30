# Chams

Chams interno para Minecraft Java (< 1.14.4), feito para aprender um pouco sobre como um jogo de verdade é renderizado.

- `Core/`: Contém a inicialização da dll e criação da thread com console.
- `OpenGL/`: Inicialização e configuração dos hooks utilizando **MinHook**.
- `Features/`: Funções que serão aplicadas nos hooks.

## Como Usar
1. Baixe a dll na aba "Releases".
2. Utilize qualquer injetor para injetar a dll no processo do minecraft (`javaw`).
3. Pressione `End` para fechar o console e desativar os hooks.

---

Inspirado™ nesses posts feitos pelo [Yotic](https://github.com/Yoticc/):
- https://www.unknowncheats.me/forum/minecraft/658762-rendering-minecraft-creating-esp-minecraft-versions-jni.html
- https://www.unknowncheats.me/forum/opengl/658596-introduction-nsight-graphics-render-api-debugger.html