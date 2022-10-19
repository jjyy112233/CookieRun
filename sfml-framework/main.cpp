#include <SFML/Graphics.hpp> //라이브러리 같은 애들은 꺽새를 사용
#include "Framework/Framework.h" //내가 추가한 파일은 큰따움표로 하기

int main()
{
    Framework framwork(1280, 720);
    framwork.Init();
    framwork.Do();

    return 0;
}