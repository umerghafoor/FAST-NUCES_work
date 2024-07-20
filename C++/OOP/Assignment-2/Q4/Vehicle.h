
class Vehicle{
private:
	char registrationNumber[20];
	char make[20];
	int yearOfManufacture;
	double currentValue;
public:
	// provide definitions of following functions...
	Vehicle();// default constructor
	Vehicle(char* str);
	Vehicle(double);
	Vehicle(const Vehicle&);
	//implement mutators for all private data members
	//implement accessors for all private data members
	void setRegistrationNumber(char* regNumber);
	void setMake(char* carMake);
	void setYearOfManufacture(int year);
	void setCurrentValue(double value);

	const char* getRegistrationNumber() const;
	const char* getMake() const;
	int getYearOfManufacture() const;
	double getCurrentValue() const;
	
	//you have to implement the following functions
	// think about the parameters required and return type of the following	functions
	void addVehicle(Vehicle arr[], int&);//adds a new vehicle
	int ageOfVehicle(int);//returns age of vehicle on the basis of year passed
	void getVehicleDetails() const;//return detail of vehicle
	void getVehicleDetailsAtIndex(Vehicle arr[], int);//return detail of vehicle stored at certain index
	bool isMatching(Vehicle);//returns true if passed vehicle matches with it
	Vehicle* returnByMake(Vehicle arr[], char*,int&);//returns the array of vehicles of specific make
	Vehicle* returnByValue(Vehicle arr[], double,int&);//returns the array of vehicles of specific value
	Vehicle* returnByYear(Vehicle arr[], int,int&);//returns the array of vehicles of specific year
	void vehicleSold(Vehicle arr[], int);//deletes the specific vehicle once its sold
	~Vehicle();
};