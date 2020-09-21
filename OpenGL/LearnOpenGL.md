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


## Vertex Shader : 정점 셰이더 
```glsl
#version 330 core
layout (local = 0) in vec3 aPos;

void main()
{
    # predefined variable
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
```