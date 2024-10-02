
class Vehicle
{
public:
    Vehicle(string id);
    virtual ~Vehicle() {}
    virtual bool canHover() const {return true;}
    virtual string description() const = 0;
    string id() const {return m_id;}
    
private:
    string m_id;
    string m_description;
};

class Drone: public Vehicle
{
public:
    Drone(string id);
    virtual ~Drone();
    virtual string description() const;
};

class Balloon: public Vehicle
{
public:
    Balloon(string id, long diameter);
    virtual ~Balloon();
    virtual string description() const;
private:
    long m_diameter;
};

class Satellite: public Vehicle
{
public:
    Satellite(string id);
    virtual ~Satellite();
    virtual string description() const;
    bool canHover() const {return false;};
};

Vehicle::Vehicle(string id)
:m_id(id), m_description("Vehicle")
{}

Drone::Drone(string id): Vehicle(id){}

Drone::~Drone(){
    cout << "Destroying " << id() << ", a drone" << endl;;
}

string Drone::description() const {return "a drone";}

Balloon::Balloon(string id, long diameter): Vehicle(id), m_diameter(diameter){}

Balloon::~Balloon(){
    cout << "Destroying the balloon " << id() << endl;
}

string Balloon::description() const {
    if(m_diameter < 8)
        return "a small balloon";
    else
        return "a large balloon";
}

Satellite::Satellite(string id): Vehicle(id){}

Satellite::~Satellite(){
    cout << "Destorying the sattellite " << id() << endl;
}

string Satellite::description() const {return "a satellite";}





