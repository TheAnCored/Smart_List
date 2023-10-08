#include "header.hpp"

std::unique_ptr<double[]> input_by_console(size_t length){

    std::unique_ptr<double[]> inpSegments = std::make_unique<double[]>(2 * length);

    std::cout<< "Input elements of list: "<< std::endl;

    for(size_t i=0; i<length; ++i){
        
        std::cout<<"["<< i+1 <<"] element: "; std::cin>> inpSegments[2*i] >>inpSegments[2*i+1];

        while(abs(inpSegments[2*i] - inpSegments[2*i+1]) < std::numeric_limits<double>::epsilon()*std::max(inpSegments[2*i], inpSegments[2*i+1])){
            std::cout<<"\n You have write equals digits. Try input again!\n\n";
            
            std::cout<<"["<< i+1 <<"] element: "; std::cin>> inpSegments[2*i] >>inpSegments[2*i+1];
        }

         if(inpSegments[2*i]>inpSegments[2*i+1]){
            double tmp = inpSegments[2*i];
            inpSegments[2*i] = inpSegments[2*i+1];
            inpSegments[2*i+1] = tmp;
        }

        std::cout<<" Read: ["<<inpSegments[2*i]<<", "<< inpSegments[2*i+1]<<"]\n\n";
    }

    return std::move(inpSegments);
}

// Output of list
void output_list(List list){

    for(size_t i = 0; i < list.length_; i++){
        if(i==0){
            std::cout<<" ["<< list.first_link_->segment_[0]<<", "<< list.first_link_->segment_[1]<<"]"<<std::endl;
            list.current_link_ = list.first_link_;
        }
        else{
            list.current_link_ = list.current_link_->next_link_;
            std::cout<<" ["<< list.current_link_->segment_[0] <<", "<< list.current_link_->segment_[1]<<"]"<<std::endl;
        }
    }
}