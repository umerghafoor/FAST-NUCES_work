class Circle {
private:
	int x;
	int y;
	float radius;
public:
	// provide definitions of following functions...
	Circle();// default constructor
	Circle(int x, int y);
	Circle(int x, int y, int radius);
	//you have to implement the following functions
	// think about the parameters required and return type of the following functions
	void setCenter(int,int);//set center of a circle
	void setRadius(int);//set radius of acircle
	int getArea();//prints area of a circle
	Circle returnLargestCircle(Circle CircleArr[],int);//return the largest circle from the array of circles
	bool overlapping(Circle,Circle);//determines of two circles are overlapping or not
	Circle* overlappingCircles(Circle CircleArr[],int);//returns an array of circles overlapping the largest circle
	void PrintCoordinate();
	int getRadius();
	~Circle();
};