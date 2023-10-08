#include "unidirectional_list.hpp"


//---------------- Links ---------------------------------

//---------------- Constructors --------------------------
// Standart constructor for empty link
Link::Link(){

    this->next_link_ = nullptr;
    this->segment_ = std::make_unique<double[]>(2);
    this->segment_[0] = 0.; this->segment_[1] = 0.; 
}

Link::Link(double st_seg, double end_seg, std::shared_ptr<Link> next_link){

    this->segment_[0] = st_seg;
    this->segment_[1] = end_seg;

    this->next_link_ = next_link;
}

// Constructor for link with segment
Link::Link( std::unique_ptr<double[]> array){

    this->next_link_ = nullptr;
    this->segment_ = std::move(array);
}

// Constructor for link with segment and next link
Link::Link( std::unique_ptr<double[]> array, std::shared_ptr<Link> next_link){

    this->next_link_ = std::move(next_link);
    this->segment_ = std::move(array);
}

// Constructor for link without segment
Link::Link( std::shared_ptr<Link> next_link){

    this->next_link_ = std::move(next_link);
    this->segment_ = std::make_unique<double[]>(2);

    this->segment_[0] = 0.; this->segment_[1] = 0.;
}

// Copying constructor
Link::Link( std::shared_ptr<Link>& second_link){
    this->next_link_ = second_link->next_link_;
    
    this->segment_[0] = second_link->segment_[0];
    this->segment_[1] = second_link->segment_[1];
}

//------------------------------------------------------
/** Methods and operators for Link **/

// Movement assignment operator
Link& Link::operator=(Link link){

    this->next_link_ = link.next_link_;
    this->segment_ = std::move(link.segment_);

    link.next_link_ = nullptr;

    return *this;
}

// Method for research of intersection two segments
bool Link::Intersection(const std::shared_ptr<Link> second_link){
    
    if(
    // -----------------[t1______{A_____t2]_____B}------------
    (this->segment_[0] > second_link->segment_[0] || abs(this->segment_[0] - second_link->segment_[0]) <= 
    std::max(this->segment_[0], second_link->segment_[0])*std::numeric_limits<double>::epsilon()) 
            && 
    (this->segment_[0] < second_link->segment_[1] || abs(this->segment_[0] - second_link->segment_[1]) <= 
    std::max(this->segment_[0], second_link->segment_[1])*std::numeric_limits<double>::epsilon())){  return true; }

    
    else if( 
    // ------------------------{A______[t1_____B}______t2}----
    (this->segment_[1] > second_link->segment_[0] || abs(this->segment_[1] - second_link->segment_[0]) <= 
    std::max(this->segment_[1], second_link->segment_[0])*std::numeric_limits<double>::epsilon()) 
            && 
    (this->segment_[1] < second_link->segment_[1] || abs(this->segment_[1] - second_link->segment_[1]) <= 
    std::max(this->segment_[1], second_link->segment_[1])*std::numeric_limits<double>::epsilon())){ return true; }

    
    else if(
    // -----------------------{A_____[t1_______t2]______B}----    
    (this->segment_[0] < second_link->segment_[0] || abs(this->segment_[0] - second_link->segment_[0]) <= 
    std::max(this->segment_[0], second_link->segment_[0])*std::numeric_limits<double>::epsilon()) 
            && 
    (this->segment_[1] > second_link->segment_[1] || abs(this->segment_[1] - second_link->segment_[1]) <= 
    std::max(this->segment_[1], second_link->segment_[1])*std::numeric_limits<double>::epsilon())){ return true; }

    else{ return false; }
}

// Method for combining two intersecting segments
void Link::Combining(const std::shared_ptr<Link> second_link){

    if( // -----------------[t1______{A_____t2]_____B}------------
    (this->segment_[0] > second_link->segment_[0] || abs(this->segment_[0] - second_link->segment_[0]) <= 
    std::max(this->segment_[0], second_link->segment_[0])*std::numeric_limits<double>::epsilon()) 
            && 
    (this->segment_[0] < second_link->segment_[1] || abs(this->segment_[0] - second_link->segment_[1]) <= 
    std::max(this->segment_[0], second_link->segment_[1])*std::numeric_limits<double>::epsilon())  )
    {
        this->segment_[0] = second_link->segment_[0];
    }

    else if(
    // ------------------------{A______[t1_____B}______t2}----    
    (this->segment_[1] > second_link->segment_[0] || abs(this->segment_[1] - second_link->segment_[0]) <= 
    std::max(this->segment_[1], second_link->segment_[0])*std::numeric_limits<double>::epsilon()) 
            && 
    (this->segment_[1] < second_link->segment_[1] || abs(this->segment_[1] - second_link->segment_[1]) <= 
    std::max(this->segment_[1], second_link->segment_[1])*std::numeric_limits<double>::epsilon()))
    {
        this->segment_[1] = second_link->segment_[1];
    }
}


// Method to extract segments 
void Link::Extract(const std::shared_ptr<Link> second_link){

    if( // -----------------[t1______{A_____t2]_____B}------------
    (this->segment_[0] > second_link->segment_[0] || abs(this->segment_[0] - second_link->segment_[0])<= 
    std::max(this->segment_[0], second_link->segment_[0])*std::numeric_limits<double>::epsilon()) 
            && 
    (this->segment_[0] < second_link->segment_[1] || abs(this->segment_[0] - second_link->segment_[1])<= 
    std::max(this->segment_[0], second_link->segment_[1])*std::numeric_limits<double>::epsilon())  )
    {
        this->segment_[0] = second_link->segment_[1];
    }


    else if(
    // ------------------------{A______[t1_____B}______t2}----    
    (this->segment_[1] > second_link->segment_[0] || abs(this->segment_[1] - second_link->segment_[0])<= 
    std::max(this->segment_[1], second_link->segment_[0])*std::numeric_limits<double>::epsilon()) 
            && 
    (this->segment_[1] < second_link->segment_[1] || abs(this->segment_[1] - second_link->segment_[1])<= 
    std::max(this->segment_[1], second_link->segment_[1])*std::numeric_limits<double>::epsilon()))
    {
        this->segment_[1] = second_link->segment_[0];
    }

    else if(
    // -----------------------{A_____[t1_______t2]______B}----    
    (this->segment_[0] < second_link->segment_[0] || abs(this->segment_[0] - second_link->segment_[0])<= 
    std::max(this->segment_[0], second_link->segment_[0])*std::numeric_limits<double>::epsilon()) 
            && 
    (this->segment_[1] > second_link->segment_[1] || abs(this->segment_[1] - second_link->segment_[1])<= 
    std::max(this->segment_[1], second_link->segment_[1])*std::numeric_limits<double>::epsilon()))
    {  
        std::shared_ptr<Link> tmp = std::make_shared<Link>(second_link->segment_[1], this->segment_[1], this->next_link_);

        this->segment_[1] = second_link->segment_[0];
        
        this->next_link_ = std::move(tmp);
    }
}
//------------------------------------------------------






//--------------- LIST ---------------------------------
//--------------- Constructors -------------------------
List::List(){
    this->first_link_ = nullptr;
    this->last_link_ = nullptr;

    this->length_ = 0;
}

List::List(size_t length_){

    for(size_t i=0; i<length_; i++){
        if(i == 0){
            
            this->first_link_ = std::make_shared<Link>();
            this->first_link_->next_link_ = nullptr;
    
            this->current_link_ = this->first_link_;
            this->last_link_ = this->first_link_;
        }
        else if((i < length_-1) && (i > 0)){ 
            
            this->current_link_->next_link_ = std::make_shared<Link>();
            this->current_link_ = this->current_link_->next_link_;

        }
        else{

            this->current_link_->next_link_ = std::make_shared<Link>();
            this->last_link_ = this->current_link_->next_link_;
        }
    }

    this->length_ = length_;
}

List::List(size_t length_, std::unique_ptr<double[]> links){

    this->length_ = length_;

    for(size_t i = 0; i < this->length_; ++i){

        if(i == 0){
            
            this->first_link_ = std::make_shared<Link>();
            this->first_link_->next_link_ = nullptr;

            this->first_link_->segment_[0] = links[2*i];
            this->first_link_->segment_[1] = links[2*i+1];
          
    
            this->current_link_ = this->first_link_;
            this->last_link_ = this->first_link_;
        }
        else if((i < length_-1) && (i > 0)){ 
            
            this->current_link_->next_link_ = std::make_shared<Link>();
            this->current_link_ = this->current_link_->next_link_;

            this->current_link_->segment_[0] = links[2*i];
            this->current_link_->segment_[1] = links[2*i+1];
        }
        else{

            this->current_link_->next_link_ = std::make_shared<Link>();
            this->last_link_ = this->current_link_->next_link_;

            this->last_link_->segment_[0] = links[2*i];
            this->last_link_->segment_[1] = links[2*i+1];
        }

    }
}
// -----------------------------------------------------

// ------ Methods --------------------------------------

// Insert elements into list
void List::App(std::unique_ptr<double[]> add_segment){

    this->current_link_ = this->first_link_;
    std::shared_ptr<Link> tmp = std::make_shared<Link>(std::move(add_segment));

    for(size_t i=1, count=0; i <= this->length_; ++i){
        if(this->current_link_->Intersection(tmp)){
            this->current_link_->Combining(tmp);
            
            tmp->segment_[0] = this->current_link_->segment_[0];
            tmp->segment_[1] = this->current_link_->segment_[1];

            count++;
            this->current_link_ = this->current_link_->next_link_;
        }

        if(count == 0 && i == this->length_){
            this->current_link_->next_link_ = tmp;
            this->length_++;
        }
    }
}

// Delete elements in list
void List::Pop(std::unique_ptr<double[]> pop_segment){

    this->current_link_ = this->first_link_;
    std::shared_ptr<Link> tmp = std::make_shared<Link>(std::move(pop_segment));

    for(size_t i=1; i<=this->length_; ++i){
        if(this->current_link_->Intersection(tmp)){
            this->current_link_->Extract(tmp);
        }
    }
}

//------------------------------------------------------