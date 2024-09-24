#include <iostream>
#include <unordered_map>
#include <string>

// Prototype interface
class Enemy {
public:
    virtual Enemy* clone() const = 0;
    virtual void showInfo() const = 0;
    virtual ~Enemy() {}
};

// Concrete prototype for Goblin
class Goblin : public Enemy {
private:
    int health;
    std::string weapon;
public:
    Goblin(int hp, std::string wp) : health(hp), weapon(wp) {}

    Enemy* clone() const override {
        return new Goblin(*this);  // Clone the object
    }

    void showInfo() const override {
        std::cout << "Goblin with " << health << " health, weapon: " << weapon << std::endl;
    }
};

// Concrete prototype for Skeleton
class Skeleton : public Enemy {
private:
    int health;
    std::string weapon;
public:
    Skeleton(int hp, std::string wp) : health(hp), weapon(wp) {}

    Enemy* clone() const override {
        return new Skeleton(*this);
    }

    void showInfo() const override {
        std::cout << "Skeleton with " << health << " health, weapon: " << weapon << std::endl;
    }
};

// Prototype registry for managing prototypes
class PrototypeRegistry {
private:
    std::unordered_map<std::string, Enemy*> prototypes;
public:
    void addPrototype(std::string type, Enemy* prototype) {
        prototypes[type] = prototype;
    }

    Enemy* createClone(std::string type) {
        return prototypes[type]->clone();
    }

    ~PrototypeRegistry() {
        for (auto& pair : prototypes) {
            delete pair.second;
        }
    }
};

int main() {
    // Create prototypes
    Goblin* goblin = new Goblin(100, "Sword");
    Skeleton* skeleton = new Skeleton(120, "Axe");

    // Register prototypes
    PrototypeRegistry registry;
    registry.addPrototype("Goblin", goblin);
    registry.addPrototype("Skeleton", skeleton);

    // Clone and create new enemies
    Enemy* newGoblin = registry.createClone("Goblin");
    Enemy* newSkeleton = registry.createClone("Skeleton");

    newGoblin->showInfo();  // Output: Goblin with 100 health, weapon: Sword
    newSkeleton->showInfo(); // Output: Skeleton with 120 health, weapon: Axe

    // Clean up
    delete newGoblin;
    delete newSkeleton;

    return 0;
}
