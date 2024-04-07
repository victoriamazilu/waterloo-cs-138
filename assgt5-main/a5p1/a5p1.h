#include <vector>
#include <string>

class Animal {
    public:
		virtual ~Animal ();
		virtual std::string speak () const = 0 ;
    protected:
		Animal (std::string name);
		std::string getName () const;
    private:
		std::string name;
};

class Dog : public Animal {
    public:
		Dog (std::string name);
		virtual ~Dog ();
		virtual std::string speak () const;
};

class Sheep : public Animal {
    public:
		Sheep (std::string name);
		virtual ~Sheep ();
		virtual std::string speak () const;
};

class Flock {
    public:
		Flock (std::string dogName);
		virtual ~Flock ();
		void addSheep (std::string name);
		std::string soundOff () const ;
    private:
		Dog *dog;
		std::vector<Sheep*> sheepList;
};
