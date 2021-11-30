#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <QGraphicsRectItem>

class GameEntity: public QGraphicsRectItem
{
public:

    /*enum classes to help differentiate the derived classes */
    enum class CATEGORY{
        TANK,
        BULLET,
        BLOCK,
        WALL
    };
    enum class CLASS {
        NONE,
        BASIC,
        ENEMY,
        TURRET
    };
    
    /*
    *  @funct:  destructor of the GameEntity
    *  @param:  N/A   
    *  @return: N/A
    */
    ~GameEntity() = default;


    /* Accesors */
    /*
    *  @funct:  get the max health of the GameEntity
    *  @param:  N/A   
    *  @return: double: max health of the GameEntity
    */
    double get_max_health() const;

    /*
    *  @funct:  get the health of the GameEntity
    *  @param:  N/A   
    *  @return: double: health of the GameEntity
    */
    double get_health() const;

    /*
    *  @funct:  get the health regen of the GameEntity
    *  @param:  N/A   
    *  @return: double: health regen of the GameEntity
    */
    double get_health_regen() const;

    /*
    *  @funct:  get the size of the GameEntity
    *  @param:  N/A   
    *  @return: int: size of the GameEntity
    */
    int get_size() const;

    /*
    *  @funct:  get the speed of the GameEntity in the x axis
    *  @param:  N/A   
    *  @return: double: speed of the GameEntity in the x axis
    */
    double get_vx() const;

    /*
    *  @funct:  get the speed of the GameEntity in the y axis
    *  @param:  N/A   
    *  @return: double: speed of the GameEntity in the y axis
    */
    double get_vy() const;

    /*
    *  @funct:  get the experience point of the GameEntity 
    *  @param:  N/A   
    *  @return: double: experience of the GameEntity
    */
    double get_xp() const;

    /*
    *  @funct:  get the level of the GameEntity 
    *  @param:  N/A   
    *  @return: int: level of the GameEntity
    */
    int get_level() const;

    /* Mutator */
    
    /*
    *  @funct:  set the max health for the GameEntity
    *  @param:  max_health: the new max health for the GameEntity
    *  @return: N/A     
    */
    void set_max_health(double max_health);
    
    /*
    *  @funct:  set the health for the GameEntity
    *  @param:  health: the new health for the GameEntity
    *  @return: N/A     
    */
    void set_health(double health);

    /*
    *  @funct:  set the health regen for the GameEntity
    *  @param:  health_regen: the new health_regen for the GameEntity
    *  @return: N/A     
    */
    void set_health_regen(double health_regen);

    /*
    *  @funct:  set the size for the GameEntity
    *  @param:  size: the new size for the GameEntity
    *  @return: N/A     
    */
    void set_size(int size);
    
    /*
    *  @funct:  set the movement speed in the x axis for the GameEntity
    *  @param:  vx: the new movement speed in the x axis for the GameEntity
    *  @return: N/A     
    */
    void set_vx(double vx);

    /*
    *  @funct:  set the movement speed in the y axis for the GameEntity
    *  @param:  vy: the new movement speed in the y axis for the GameEntity
    *  @return: N/A     
    */
    void set_vy(double vy);

    /*
    *  @funct:  set the experience point for the GameEntity
    *  @param:  xp: the new experience point for the GameEntity
    *  @return: N/A     
    */
    void set_xp(double xp);

    /*
    *  @funct:  set the level for the GameEntity
    *  @param:  level: the new level for the GameEntity
    *  @return: N/A     
    */
    void set_level(int level);

    /* Virtual functions to differentiate the derived classes*/
    
    /*
    *  @funct:  get the category of the GameEntitiy, pure virtual function such that every dervied object can be differentiated through GameEntity::CATEGORY 
    *  @param:  N/A
    *  @return: GameEntity::CATEGORY: the category of GameEntity
    */
    virtual GameEntity::CATEGORY get_category() const = 0;
    
    /*
    *  @funct:  get the class of the GameEntitiy, virtual function such the object can be differentiated through GameEntity::CLASS 
    *  @param:  N/A
    *  @return: GameEntity::CLASS: the class of GameEntity
    */
    virtual GameEntity::CLASS get_class() const;

private:
    /* Private data memebers, defaults to nothing */
    double max_health {};  
    double health {};
    double health_regen {};

    int size{};
    double vx{}, vy{};
    double xp{};
    int level{};

protected:
    /*
    *  @funct:  the constructor for the GameEntitiy, in protected type so that no GameEntity can be created
    *  @param:  health: initial health for the GameEntity, health_regen: initial health regen for the GameEntity, max_health: initial max_health for the GameEntity,
    *  @param:  size: initial size for the GameEntity, vx: initial movement speed in the x axis for the GameEntity, vy: initial movement speed in the y axis for the GameEntity,
    *  @param:  xp: initial experience point for the GameEntity, level: initial level for the GameEntity    
    *  @return: N/A     
    */
    GameEntity(const double& health, const double& health_regen, const double& max_health, const int& size,
               const double& vx, const double& vy,const double& xp,const int& level);

};

#endif // GAMEENTITY_H
