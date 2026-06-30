#include <iostream>
#include <cmath>

int main(){
  float a, b, c;
  std::cout << "a, b, c: \n";  //>> std::endl
  std::cin >> a;  std::cin >> b;  std::cin >> c;
  float discriminant = b*b - 4 * a * c;std::cout <<"discriminant = "<<discriminant<<std::endl;
  if (discriminant < 0){ 
    std::cout << "Not a quadratic equation!" << std::endl;
  }else if (a + b + c == 0) { //Check a+b+c=0 → return x1=1 and x2=c/a.
    std::cout  << "1) Root x1 = "<< 1 <<", Root x2 = "<< c/a << std::endl;
  }else if (a + c == b) {  //Check a+c=b → return -1 and −c/a.
    std::cout  << "2) Root x1 = "<< -1 <<", Root x2 = "<< -c/a << std::endl;
  }else if (discriminant > 0){
      float x1 = (-b + std::sqrt(discriminant)) / (2  * a);
      float x2 = (-b - std::sqrt(discriminant))/(2*a);
      std::cout  << "3) Root x1 = "<<x1<<", Root x2 = "<< x2 << std::endl;
  }else if (discriminant == 0){
      float x = -b/(2*a);
      std::cout << "Root: " << x << std::endl;
  }else{
      std::cout << "Complex scenario is not supported!" << std::endl;
  }
     return 0;
}
/*


Если a=1, попробовать подобрать корни по Виету (перебор делителей c).
Если b чётное — использовать D/4.
И только если ничего не сработало — считать обычный дискриминант.

int main() {
  //std::cout <<"Hello World"<<std::endl;
  std::cout << "A new commit of the change so mine.\n";
  std::cout <<"A new 'Commit 2' of the change so mine.\n";
  
  std::cout <<"Created a new development branch — git branch dev.\n";
  std::cout <<"Made a git commit -m 'first dev commit'.\n";
  std::cout <<"Made a git commit -m 'second dev commit'.\n";
  std::cout <<"Made a git commit -m 'third dev commit'.\n";
  
  std::cout << "Ночь, улица, фонарь, аптека,\n";

}

std::cout <<"A new 'Commit 3' of the change so mine.\n";

std::cout << "Бессмысленный и тусклый свет.\n";
std::cout << "Живи ещё хоть четверть века —\n";
std::cout << "Всё будет так. Исхода нет.\n";
  */