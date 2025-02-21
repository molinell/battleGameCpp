#ifndef WEAPON
#define WEAPON

#include <string>
#include <vector>
#include <unordered_map>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>

class Weapon
{

public:

    /**
     * @brief Enum for weapon types
     */
    enum Types {
        SWORD,
        FIREARM,
        FIST,
        MACE,
        CROSSBOW,
        SPEAR,
        AXE,
        POTION
    };

    Weapon() = default;

    /**
     * @brief Construct a new Weapon object
     * 
     * @param type the type of the weapon
     */
    Weapon(Types type) {
       const auto& prop = properties_.at(type);
       name_ = prop.name;
       damage_ = prop.damage;
       wear_ = prop.wear;
       health_ = 100;
       type_ = type;
    }

    /**
     * @brief Copy constructor
     * 
     * @param other the weapon to copy
     */
    Weapon(Weapon* other): 
        name_(other->name_), damage_(other->damage_), wear_(other->wear_), health_(other->health_), type_(other->type_){}

    ~Weapon(){}

    const std::string& getName() const;
    Weapon::Types getType() const;
    int getDamage() const;
    double getHealth() const;
    
    /**
     * @brief Wears down the weapon (reduce health)
     * 
     * @return double the health of the weapon
     */
    double wearDown();


private:
    std::string name_;
    int damage_;
    double wear_;
    double health_;
    int price_;
    Types type_;

    /**
     * @brief A struct for the properties of a specific weapon type
     * 
     * @param name the string name of the weapon type
     * @param damage the max damage the weapon can cause
     * @param wear the amount health should be reduced per use
     * @param price the cost of the weapon
     */
    struct Properties {
        std::string name;
        int damage;
        double wear;
        int price;
    };

    /**
     * @brief Map of default weapon types
     */
    static const std::unordered_map<Types, Properties> properties_;

    friend class boost::serialization::access;
    /**
     * @brief Serialises a Weapon object
     * 
     * @tparam Archive 
     * @param ar the archive to write to
     * @param version 
     */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version){
        ar & name_;
        ar & damage_;
        ar & wear_;
        ar & health_;
        ar & type_;
    }
};

#endif
