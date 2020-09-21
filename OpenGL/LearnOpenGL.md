# Hello Triangle

## Normalized Device Coordinates (NDC) : 정규화 좌표계
- 정점 좌표가 정점 셰이더에서 처리되면 정규화 좌표 x, y 그리고 z 에서 -1.0 ~ 1.0 로 표현된 작은 공간입니다. 이범위를 벗어나는 좌표는 절단되어 화면에 표시되지 않습니다. 
- 화면 좌표는 뷰포트(glViewport) 변환을 통해 정규화 좌표계로 치환됩니다.

## Vertex Buffer Object (VBO) : 정점 버퍼 오브젝트 
- 정점 버퍼 오브젝트 GPU 의 메모리에 많은 수의 정점을 저장할 수 있습니다. 이러한 버퍼 객체를 사용하는 이점은 한 번에 한 정점 씩 데이터를 보낼 필요없이 대량의 데이터를 한 번에 그래픽 카드로 보내고 충분한 메모리가 남아있는 경우 그대로 유지할 수 있다는 것입니다. CPU에서 그래픽 카드로 데이터를 보내는 것은 비교적 느리기 때문에 가능한 한 많은 데이터를 한 번에 보내려고 할 수 있습니다. 데이터가 그래픽 카드의 메모리에 있으면 정점 셰이더가 정점에 거의 즉각적으로 액세스하여 매우 빠릅니다.

```cpp
unsigned int vbo
glGenBuffers(1, &vbo); // 해당 버퍼에 해당하는 고유 ID 할당
glBindBuffer(GL_ARRAY_BUFFER, VBO); // GL_ARRAY_BUFFER 타겟에 바인딩 
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 바인딩 된 버퍼의 메모리에 값 복사 
```
## 그래픽 카드가 주어진 데이터를 관리하는 방법
- GL_STREAM_DRAW : 데이터가 한 번만 설정되고 GPU에서 최대 몇 번만 사용됩니다.
- GL_STATIC_DRAW : 데이터가 한 번만 설정되고 여러 번 사용됩니다.
- GL_DYNAMIC_DRAW : 데이터가 많이 변경되고 여러 번 사용됩니다.

## Shader
```glsl
// Vertex Shader

#version 330 core
layout (local = 0) in vec3 aPos;

void main()
{
    # gl_position : predefined variable
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
```

```glsl
// Fragment Shader
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f); // Red Color 
}

```

## Shader Compile : 셰이더 컴파일
```cpp
const char* vertexShaderSource; // Load Shader Source (*.glsl)

unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); // Vertex 세이더 생성 
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); 
glCompileShader(vertexShader); // 셰이더 컴파일

// 컴파일 성공여부 확인
int success;
char infoLog[512];
glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
if(!success)
{
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "Compile failed" << infoLog << std::endl;
})

// Fragment 셰이더는 Shader type(GL_FRAGMENT_SHADER) 을 제외하고 Vertex Shader 와 동일하게 컴파일을 진행한다.
```

## Shader Program : 셰이더 프로그램
- 셰이더 프로그램 개체는 결합 된 여러 셰이더의 최종 링크 버전입니다. 최근에 컴파일된 셰이더를 사용하려면 링크된 셰이더 프로그램 개체를 추가 한 다음 개체를 렌더링 할 때에 셰이더 프로그램을 활성화 한다.

```cpp
unsigned int shaderProgram = glCreateProgram();
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);
glLinkProgram(shaderProgram);

// 셰이더 프로그램 연결이 실패했는지 확인
int success;
char infoLog[512];
glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
if(!success)
{
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "Link failed" << infoLog << std::endl;
}

// 프로그램 활성화 
glUseProgram(shaderProgram);

// Link 가 완료된 셰이더 객체는 삭제 
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);
```

## Linking Vertex Attribute : 정점 속성 연결
- 정점 셰이더를 사용하면 정점 속성의 형태로 원하는 입력을 지정할 수 있으며, 이는 유연성을 크게 허용하지만 입력 데이터의 어떤 부분이 정점 셰이더의 어떤 정점 속성으로 이동하는지 수동으로 지정해야 함을 의미합니다. 이는 OpenGL이 렌더링 전에 정정 데이터를 해석하는 방법을 지정해야 함을 의미합니다.
- 정점 속성은 현재 GL_ARRAY_BUFFER에 바인딩 된 VBO 에 의해 결정됩니다.
```cpp
// 0. copy our vertices array in a buffer for OpenGL to use
glBindBuffer(GL_ARRAY_BUFFER, vbo); 
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// 1. then set the vertex attributes pointers
glVertexAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // 첫 번째 매개 변수는 정점 속성을 지정합니다.
glEnableVertexAttribute(0); // 정점 속성을 활성화
// 2. use our shader program when we want to render an object
glUseProgram(shaderProgram);
// 3. now draw the object
```

## Vertex Array Object (VAO) : 정점 배열 객체

```cpp
unsigned int vao;
glGenVertexArrays(1, &vao);
// 1. bind vertex array object
glBindVertexArray(vao);
// 2. copy our vertics array in a buffer for OpenGL to use
glBindBuffer(GL_ARRAY_BUFFER, vbo);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), GL_STATIC_DRAW);
// 3. then set our vertex attributes pointers
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); 
glEnableVertexAttribAray(0);

// 4. draw the object
glUseProgram(shaderProgram);
glBindVertexArray(vao);
glDrawArrays(GL_TRIANGLES, 0, 3);
```

## Element Buffer Object (EBO) : 요소 버퍼 객체

```cpp
unsigned int ebo;
glGenBuffers(1, &ebo); // 요소 버퍼 객체 생성

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


```