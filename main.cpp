#include <iostream>
#include "header.hpp"


int main(){

    size_t length=0;
    char answ='a';

    std::cout<< " Input length of list: "; std::cin >> length; std::cout <<std::endl;

    std::unique_ptr<double[]> array = input_by_console(length);

    List list(length, std::move(array));

    output_list(list);

    do{
        std::cout << "\n What do you want to do?(App(A), Pop(P), Output(O), Nothing(N)) \n"; std::cin >> answ;

        if(answ>90){ answ -= 32; }
        if(answ == 'n' || answ == 'N'){ break;}
        

        switch(answ){
            case 'A': 
            {
                std::unique_ptr<double[]> tmp = std::make_unique<double[]>(2);
                std::cout<< " Input segment to add in list: "; std::cin>> tmp[0] >> tmp[1]; std::cout<<std::endl;

                if(tmp[0]>tmp[1]){
                    double tmpd = tmp[0];
                    tmp[0] = tmp[1];
                    tmp[1] = tmpd;
                }

                list.App(std::move(tmp));
                output_list(list);
                
            } break;

            case 'P':
            {
                std::unique_ptr<double[]> tmp = std::make_unique<double[]>(2);
                std::cout<< " Input segment to pop from list: "; std::cin>> tmp[0] >> tmp[1];
 
                if(tmp[0]>tmp[1]){
                    double tmpd = tmp[0];
                    tmp[0] = tmp[1];
                    tmp[1] = tmpd;
                }
               
                list.Pop(std::move(tmp));

                if(list.length_ == 0){ 
                    std::cout<< "\n\n List is empty! \n\n"; 
                }
                else{ output_list(list); }
            } break;

            case 'O':
            {
                output_list(list);
            } break;

            default: break;
        }

    }while(answ != 'N' || answ != 'n');

    std::cout<< "------------ Program finished! ------------\n\n";

    return 0;
}