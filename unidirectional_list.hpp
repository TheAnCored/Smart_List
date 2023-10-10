#include <iostream>
#include <limits>
#include <memory>

class Link{
public:
	// It is a link on the next element of list
	std::shared_ptr<Link> next_link_;

	// It is a segment wich include start and end double points
	std::unique_ptr<double[]> segment_;

	// ----------------------------------------
	// Standart constructor without arguments
	Link();

	// Constructor with the segment as two digits and next_link
	Link( double, double, std::shared_ptr<Link>);
	Link(double, double);

	// Constructor with the segment
	Link( std::unique_ptr<double[]>);

	// Constructor with the segment and the next link
	Link( std::unique_ptr<double[]>, std::shared_ptr<Link>);

	// Constructor for link without segment
	Link( std::shared_ptr<Link>);

	// Copying constructor
	Link( std::shared_ptr<Link>&);

	// Destructor
	~Link(){};

	// Operator =
	Link& operator=(Link);

	void output_link();

	// Method of comparsion segments on intersection
	bool Intersection(const std::shared_ptr<Link>);

	// Method of combining sections
	void Combining(const std::shared_ptr<Link>);

	// Method to extract segments
	void Extract(const std::shared_ptr<Link>, size_t& );
};

class List{
public:
	// Extreme links
	std::shared_ptr<Link> first_link_; // Start of the list
	std::shared_ptr<Link> last_link_; // End of the list

	std::shared_ptr<Link> current_link_; // Current link

	size_t length_; // Length of the list

	// Standart constructor without info
	List();

	// Contructor wich have a length of list
	List(size_t length);

	// It is constructor wich have length and links in array
	List(size_t, std::unique_ptr<double[]>);

	~List(){};	
	// ------ Methods -----------------------------------

	// Output list
	void output_list();

	void RemIntersect();

	// ------ Add segments in the list
	void App(std::unique_ptr<double[]>); // Add segment at the random place

	// ------ Remove segments from the list
	void Pop(std::unique_ptr<double[]>); // Pop from other place
};