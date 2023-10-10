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

    this->segment_ = std::make_unique<double[]>(2);

    this->segment_[0] = st_seg;
    this->segment_[1] = end_seg;
    
    this->next_link_ = next_link;
}

Link::Link(double st_seg, double end_seg){

    this->segment_ = std::make_unique<double[]>(2);

    this->segment_[0] = st_seg;
    this->segment_[1] = end_seg;
    
    this->next_link_ = nullptr;
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

void Link::output_link(){
    std::cout<<"[ "<<this->segment_[0]<<", "<<this->segment_[1]<<"]"<<std::endl;
}

// Method for research of intersection two segments
bool Link::Intersection(const std::shared_ptr<Link> second_link){

    if( // ---- t1 <= A && A <= t2
        (abs( this->segment_[0]-second_link->segment_[0] )< std::numeric_limits<double>::epsilon()*std::max(abs(this->segment_[0]),abs(second_link->segment_[0]))
        || 
        this->segment_[0] > second_link->segment_[0])
        &&
        (abs( this->segment_[0]-second_link->segment_[1] )< std::numeric_limits<double>::epsilon()*std::max(abs(this->segment_[0]),abs(second_link->segment_[1]))
        || 
        this->segment_[0] < second_link->segment_[1])
    ){ return true; }

    else if( // ---- t1 <= B <= t2 ----
        (abs( this->segment_[1]-second_link->segment_[0] )< std::numeric_limits<double>::epsilon()*std::max(abs(this->segment_[1]),abs(second_link->segment_[0]))
        ||
        this->segment_[0] > second_link->segment_[0])
        &&
        (abs( this->segment_[1]-second_link->segment_[1] )< std::numeric_limits<double>::epsilon()*std::max(abs(this->segment_[1]),abs(second_link->segment_[1]))
        || 
        this->segment_[1] < second_link->segment_[1])
    ){ return true; }

    else if(// ---- A <= t1 && t2 <= B ----
        (abs( this->segment_[0]-second_link->segment_[0] )< std::numeric_limits<double>::epsilon()*std::max(abs(this->segment_[0]),abs(second_link->segment_[0]))
        || 
        this->segment_[0] < second_link->segment_[0])
        &&
        (abs( this->segment_[1]-second_link->segment_[1] )< std::numeric_limits<double>::epsilon()*std::max(abs(this->segment_[1]),abs(second_link->segment_[1]))
        || 
        this->segment_[1] > second_link->segment_[1])
    ){ return true; }

    else{ return false; }
}

// Method for combining two intersecting segments
void Link::Combining(const std::shared_ptr<Link> second_link){

    if( // -----------------[t1______{A_____t2]_____B}------------ or A == t2
    (this->segment_[0] > second_link->segment_[0]) 
    && 
    (this->segment_[0] < second_link->segment_[1] || abs(this->segment_[0] - second_link->segment_[1]) <= 
    std::max(abs(this->segment_[0]), abs(second_link->segment_[1]))*std::numeric_limits<double>::epsilon())  
    &&
    this->segment_[1] > second_link->segment_[1]
    )
    {
        this->segment_[0] = second_link->segment_[0];
    }

    else if( // -----------------[t1______{A_____t2]_____B}------------ or B == t2
        (this->segment_[0] > second_link->segment_[0]) 
        && 
        (this->segment_[1] > second_link->segment_[1] || abs(this->segment_[1] - second_link->segment_[1]) <= 
        std::max(abs(this->segment_[1]), abs(second_link->segment_[1]))*std::numeric_limits<double>::epsilon())  
        &&
        this->segment_[0] < second_link->segment_[1])
    {
        this->segment_[0] = second_link->segment_[0];
    }

    else if( // --------______{A_____[t1_____B}_____t2]------------ or B == t1
        (this->segment_[0] < second_link->segment_[0]) 
            && 
        (this->segment_[1] < second_link->segment_[0] || abs(this->segment_[1] - second_link->segment_[0]) <= 
        std::max(abs(this->segment_[0]), abs(second_link->segment_[1]))*std::numeric_limits<double>::epsilon())  
            &&
        this->segment_[1] < second_link->segment_[1])
    {
        this->segment_[1] = second_link->segment_[1];
    }


    else if( // --------______{A_____[t1_____B}_____t2]------------ or A == t1
        (this->segment_[1] > second_link->segment_[0]) 
        && 
        (this->segment_[0] < second_link->segment_[0] || abs(this->segment_[0] - second_link->segment_[0]) <= 
        std::max(abs(this->segment_[0]), abs(second_link->segment_[0]))*std::numeric_limits<double>::epsilon())  
        &&
        this->segment_[1] < second_link->segment_[1])
    {
        this->segment_[1] = second_link->segment_[1];
    }

    else if(
    // --------{t1>A_______________B<t2}----    
    ( this->segment_[0] > second_link->segment_[0] ) && 
    ( this->segment_[1] < second_link->segment_[1] )
    ){
        this->segment_[0] = second_link->segment_[0];
        this->segment_[1] = second_link->segment_[1]; 
    }
}


// Method to extract segments 
void Link::Extract(const std::shared_ptr<Link> second_link, size_t& length_){


    if( // ----[t1______{A_____t2]_____B}----- 
        (this->segment_[0] > second_link->segment_[0]) 
        && 
        (this->segment_[0] < second_link->segment_[1] )
        &&
        (this->segment_[1] > second_link->segment_[1]))
    {
        this->segment_[0] = second_link->segment_[1];
    }

    else if( //----[t1_______{A1_______t2==B]}-------------
        (this->segment_[0] > second_link->segment_[0]) 
        && 
        (this->segment_[0] < second_link->segment_[1] )
        &&
        (abs(this->segment_[1] - second_link->segment_[1])<
        std::max(abs(this->segment_[1]), abs(second_link->segment_[1]))*std::numeric_limits<double>::epsilon()))
    {
        this->segment_[0] = 0.;
        this->segment_[1] = 0.;
    }

    else if( // -------{A______[t1_____B}______t2}----   
        (this->segment_[1] > second_link->segment_[0]) 
        && 
        (this->segment_[1] < second_link->segment_[1] )
        &&
        this->segment_[0] < second_link->segment_[0])
    {
        this->segment_[1] = second_link->segment_[0];
    }

    else if( //-----{A==t1_____B}_____t2]----------
        (this->segment_[1] > second_link->segment_[0]) 
        && 
        (this->segment_[1] < second_link->segment_[1] )
        &&
        ((abs(this->segment_[0] - second_link->segment_[0])<
        std::max(abs(this->segment_[0]), abs(second_link->segment_[0]))*std::numeric_limits<double>::epsilon())))
    {
        this->segment_[0] = 0.;
        this->segment_[1] = 0.;
    }

    else if( //-----{A==t1_____t2]_____B}----------
        (this->segment_[1] > second_link->segment_[1]) 
        && 
        (this->segment_[0] < second_link->segment_[1] )
        &&
        ((abs(this->segment_[0] - second_link->segment_[0])<
        std::max(abs(this->segment_[0]), abs(second_link->segment_[0]))*std::numeric_limits<double>::epsilon())))
    {
        this->segment_[0] = second_link->segment_[1];
    }

    else if( //-----{A____[t1_____t2 == B}----------
        (this->segment_[1] > second_link->segment_[0]) 
        && 
        (this->segment_[0] < second_link->segment_[0] )
        &&
        ((abs(this->segment_[1] - second_link->segment_[1])<
        std::max(abs(this->segment_[1]), abs(second_link->segment_[1]))*std::numeric_limits<double>::epsilon())))
    {
        this->segment_[1] = second_link->segment_[0];
    }

    else if( // ---------{A_____[t1_______t2]______B}----  where A != t1 and B != t2 
        (this->segment_[0] < second_link->segment_[0]) 
                && 
        (this->segment_[1] > second_link->segment_[1]))
    {  
        std::shared_ptr<Link> tmp = std::make_shared<Link>(second_link->segment_[1], this->segment_[1]);

        tmp->next_link_ = this->next_link_;

        this->next_link_ = tmp;

        this->segment_[1] = second_link->segment_[0];

        length_++;
    }

    else if( // -------{t1<=A_______B<=t2}----   
        (abs(this->segment_[0] - second_link->segment_[0])< 
        std::max(abs(this->segment_[0]), abs(second_link->segment_[0]))*std::numeric_limits<double>::epsilon() 
        || 
        second_link->segment_[0] < this->segment_[0])
            && 
        (abs(this->segment_[1] - second_link->segment_[1])<
        std::max(abs(this->segment_[1]), abs(second_link->segment_[1]))*std::numeric_limits<double>::epsilon()
        ||
        this->segment_[1] < second_link->segment_[1]))
    {
        this->segment_[0] = 0.;
        this->segment_[1] = 0.;
    }
    else{ std::cout<<"\n\n Nothing!\n\n";}
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

    this->RemIntersect();
}
// -----------------------------------------------------

// ------ Methods --------------------------------------

void List::output_list(){

    for(size_t i = 0; i < this->length_; i++){
        if(i==0){
            std::cout<<" ["<< this->first_link_->segment_[0]<<", "<< this->first_link_->segment_[1]<<"]"<<std::endl;
            this->current_link_ = this->first_link_;
        }
        else{
            this->current_link_ = this->current_link_->next_link_;
            std::cout<<" ["<< this->current_link_->segment_[0] <<", "<< this->current_link_->segment_[1]<<"]"<<std::endl;
        }
    }
}

void List::RemIntersect(){
    
    std::shared_ptr<Link> tmp = nullptr;
    std::shared_ptr<Link> prev = nullptr;

    for(size_t i=0; i<this->length_-1; i++){

        if(i==0){ this->current_link_ = this->first_link_;}
        else{ this->current_link_ = this->current_link_->next_link_;}

        for(size_t j=i+1; j < this->length_; j++){ 
            if(j == i+1){ prev = this->current_link_;}
            else{ prev = tmp;}
            tmp = this->current_link_->next_link_;

            if(this->current_link_->Intersection(tmp)){
                this->current_link_->Combining(tmp);

                prev->next_link_ = tmp->next_link_;

                this->length_--;
                i--;

                break;
            }
        }
    }
}


// Insert elements into list
void List::App(std::unique_ptr<double[]> add_segment){

    std::shared_ptr<Link> tmp = std::make_shared<Link>(std::move(add_segment));

     if(this->length_ == 0){
        this->first_link_ = tmp;
        this->length_++;

        return;
    }

    for(size_t i=0, count=0; i < this->length_; i++){
        
        if(i == 0){ this->current_link_ = this->first_link_; }
        else{ this->current_link_ = this->current_link_->next_link_; }
        

        if(this->current_link_->Intersection(tmp)){
            
            this->current_link_->Combining(tmp);

            count++;
        }

        if(count == 0 && i == this->length_-1){
            this->length_++;
            this->current_link_->next_link_ = tmp;
        }
    }

    this->RemIntersect();
}

// Delete elements in list
void List::Pop(std::unique_ptr<double[]> pop_segment){

    std::shared_ptr<Link> tmp = std::make_shared<Link>(std::move(pop_segment));


    for(size_t i=0; i < this->length_; ++i){
        if(i == 0){ this->current_link_ = this->first_link_; }
        else{ this->current_link_ = this->current_link_->next_link_; }

        if(this->current_link_->Intersection(tmp)){
            
            size_t& length = this->length_;
            this->current_link_->Extract(tmp, length);
        }
    }


    for(size_t i=0; i < this->length_; ++i){


        if(i == 0){ this->current_link_ = this->first_link_; }
        else{ 
            tmp = this->current_link_;
            this->current_link_ = this->current_link_->next_link_; 
        }

        if(
            abs(this->current_link_->segment_[0]) < std::numeric_limits<double>::epsilon()
            &&
            abs(this->current_link_->segment_[1]) < std::numeric_limits<double>::epsilon()
            && i == 0
        ){
            this->first_link_ = this->current_link_->next_link_;
            this->length_--;

            --i;
        }
        else if(
            abs(this->current_link_->segment_[0]) < std::numeric_limits<double>::epsilon()
            &&
            abs(this->current_link_->segment_[1]) < std::numeric_limits<double>::epsilon()
            && i > 0
        ){
            this->current_link_ = tmp;
            this->current_link_->next_link_ = this->current_link_->next_link_->next_link_;

            this->length_--;
        }
    }

    for(size_t i=0, count=0; i < this->length_; i++){
        if(i == 0){ this->current_link_ = this->first_link_;}
        else{ this->current_link_ = this->current_link_->next_link_;}

        if(this->current_link_->next_link_ != nullptr){
            count++;
            std::cout<<count<<" geg";
        }
    }
}

//------------------------------------------------------