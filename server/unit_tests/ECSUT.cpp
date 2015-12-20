#include <iostream>
#include "ECSUT.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"

namespace ECS
{
    /*
    ** Constructor/Destructor
    */
    ECSUT::ECSUT()
    {
    }

    ECSUT::~ECSUT()
    {
    }

    /*
    ** Public member functions
    */
    void          ECSUT::registerTests()
    {
        registerTest("EntityLifeRecyclingSimple",
                     &ECSUT::entityLifeRecyclingSimple);
        registerTest("EntityLifeRecyclingWithComponent",
                     &ECSUT::entityLifeRecyclingWithComponent);
        registerTest("DynamicComponentAddDel", &ECSUT::dynamicComponentAddDel);
        registerTest("RetrieveEntityByComponent",
                     &ECSUT::retrieveEntityByComponent);
        registerTest("SystemProcess", &ECSUT::systemProcess);
        registerTest("SystemManager", &ECSUT::systemManager);
    }

    std::string   ECSUT::getName() const
    {
        return "ECS";
    }

    /*
    ** Unit tests
    */
    void          ECSUT::entityLifeRecyclingSimple()
    {
        EntityManager&    em      = EntityManager::getInstance();
        Entity*           entity  = &(em.create());

        UT_ASSERT(entity->getId() == 0);
        UT_ASSERT(entity->getComponentMask() == 0);
        entity = &(em.create());
        UT_ASSERT(entity->getId() == 1);
        UT_ASSERT(em.destroy(0) == true);
        entity = &(em.create());
        UT_ASSERT(entity->getId() == 0);
        entity = &(em.create());
        UT_ASSERT(entity->getId() == 2);
        entity = &(em.create());
        UT_ASSERT(entity->getId() == 3);
        UT_ASSERT(em.destroy(0) == true);
        UT_ASSERT(em.destroy(1) == true);
        UT_ASSERT(em.destroy(2) == true);
        UT_ASSERT(em.destroy(3) == true);
        entity = &(em.create());
        UT_ASSERT((entity->getId() == 0 || entity->getId() == 1
        || entity->getId() == 2 || entity->getId() == 3));
        UT_ASSERT(em.destroy(entity->getId()) == true);
        em.clean();
    }

    void          ECSUT::entityLifeRecyclingWithComponent()
    {
        EntityManager&    em      = EntityManager::getInstance();
        Entity*           entity;

        em.registerComponent(std::make_unique<Sample::Component1>());
        em.registerComponent(std::make_unique<Sample::Component2>());
        em.registerComponent(std::make_unique<Sample::Component3>());

        entity = &(em.create(Sample::Component1::mask
                            | Sample::Component2::mask));
        UT_ASSERT(entity->getId() == 0);
        UT_ASSERT(entity->getComponentMask() == (Sample::Component1::mask
                                                | Sample::Component2::mask));
        entity = &(em.create(Sample::Component3::mask));
        UT_ASSERT(entity->getId() == 1);
        UT_ASSERT(em.destroy(0) == true);
        UT_ASSERT(em.destroy(1) == true);
        entity = &(em.create(Sample::Component3::mask));
        UT_ASSERT(entity->getId() == 1);
        UT_ASSERT(em.destroy(1) == true);
        entity = &(em.create(Sample::Component1::mask
                            | Sample::Component2::mask));
        UT_ASSERT(entity->getId() == 0);
        entity = &(em.create(Sample::Component1::mask
                            | Sample::Component2::mask));
        UT_ASSERT(entity->getId() == 2);
        entity = &(em.create(Sample::Component1::mask
                            | Sample::Component2::mask));
        UT_ASSERT(entity->getId() == 3);
        UT_ASSERT(em.destroy(0) == true);
        UT_ASSERT(em.destroy(1) == false);
        UT_ASSERT(em.destroy(2) == true);
        UT_ASSERT(em.destroy(3) == true);
        em.clean();
    }

    void          ECSUT::systemProcess()
    {
        EntityManager&    em      = EntityManager::getInstance();
        Sample::System1   sys;
        EntityCollection  entities;

        em.registerComponent(std::make_unique<Sample::Component1>());
        em.registerComponent(std::make_unique<Sample::Component2>());
        em.registerComponent(std::make_unique<Sample::Component3>());
        em.create(Sample::Component1::mask | Sample::Component2::mask);
        em.create(Sample::Component1::mask | Sample::Component2::mask
                    | Sample::Component3::mask);
        em.create(Sample::Component1::mask | Sample::Component2::mask
                    | Sample::Component3::mask);
        em.create(Sample::Component1::mask);
        em.create(Sample::Component2::mask);
        em.create(Sample::Component3::mask);
        em.create(Sample::Component1::mask | Sample::Component2::mask);
        em.create(Sample::Component1::mask | Sample::Component2::mask);
        UT_ASSERT(em.getByMask(Sample::Component1::mask).size() == 6);
        UT_ASSERT(em.getByMask(Sample::Component1::mask
                                | Sample::Component3::mask).size() == 2);
        sys.process();
        entities = em.getByMask(Sample::Component1::mask
                                    | Sample::Component2::mask);
        UT_ASSERT(entities.size() == 5);
        for (auto& entity: entities)
        {
            Sample::Component1*   c1;
            Sample::Component2*   c2;

            c1 = entity->getComponent<Sample::Component1>();
            UT_ASSERT(c1 != nullptr);
            c2 = entity->getComponent<Sample::Component2>();
            UT_ASSERT(c2 != nullptr);
            UT_ASSERT(c1->getData() == "Tea est trop fort");
            UT_ASSERT(c2->getData() == "Tea est trop swag");
        }
        em.clean();
    }

    void          ECSUT::systemManager()
    {
        EntityManager&    em        = EntityManager::getInstance();
        SystemManager&    sm        = SystemManager::getInstance();
        EntityCollection  entities;

        em.registerComponent(std::make_unique<Sample::Component1>());
        em.registerComponent(std::make_unique<Sample::Component2>());
        em.registerComponent(std::make_unique<Sample::Component3>());
        sm.registerSystem(std::make_unique<Sample::System1>());
        em.create(Sample::Component1::mask | Sample::Component2::mask);
        em.create(Sample::Component1::mask | Sample::Component2::mask);
        sm.processAll();
        entities = em.getByMask(Sample::Component1::mask
                                | Sample::Component2::mask);
        UT_ASSERT(entities.size() == 2);
        for (auto& entity: entities)
        {
            Sample::Component1*   c1;
            Sample::Component2*   c2;

            c1 = entity->getComponent<Sample::Component1>();
            UT_ASSERT(c1 != nullptr);
            c2 = entity->getComponent<Sample::Component2>();
            UT_ASSERT(c2 != nullptr);
            UT_ASSERT(c1->getData() == "Tea est trop fort");
            UT_ASSERT(c2->getData() == "Tea est trop swag");
        }
        em.clean();
    }

    void            ECSUT::dynamicComponentAddDel()
    {
        EntityManager&      em      = EntityManager::getInstance();
        Entity*             entity  = nullptr;

        em.registerComponent(std::make_unique<Sample::Component1>());
        em.registerComponent(std::make_unique<Sample::Component2>());
        em.registerComponent(std::make_unique<Sample::Component3>());
        entity = &em.create(Sample::Component1::mask);
        UT_ASSERT(entity->getComponentMask() == Sample::Component1::mask);
        entity->addComponent(std::make_unique<Sample::Component2>());
        UT_ASSERT(entity->getComponentMask() == (Sample::Component1::mask
                                                | Sample::Component2::mask));
        entity->removeComponent(Sample::Component1::mask);
        UT_ASSERT(entity->getComponentMask() == Sample::Component2::mask);
        entity->addComponent(std::make_unique<Sample::Component1>());
        entity->addComponent(std::make_unique<Sample::Component3>());
        UT_ASSERT(entity->getComponentMask() == (Sample::Component1::mask
                                                | Sample::Component2::mask
                                                | Sample::Component3::mask));
        entity->removeComponent(Sample::Component2::mask);
        UT_ASSERT(entity->getComponentMask() == (Sample::Component1::mask
                                                | Sample::Component3::mask));
        em.clean();
    }

    void            ECSUT::retrieveEntityByComponent()
    {
    }

    namespace Sample
    {
        /* Component1 */
        const ComponentMask   Component1::mask = Sample::COMPMASK_ONE;

        Component1::Component1() {}
        Component1::~Component1() {}

        std::string const& Component1::getData() const
        { return _data; }

        void            Component1::setData(std::string const& data)
        { _data = data; }

        std::string     Component1::getName() const
        { return "Component1"; }

        ComponentMask   Component1::getMask() const
        { return mask; }

        IComponent*     Component1::clone() const
        { return new Component1(); }

        void            Component1::clear() {}

        std::string     Component1::toString() const
        { return "Component1 {" + _data + "}\n"; }

        /* Component2 */
        const ComponentMask   Component2::mask = Sample::COMPMASK_TWO;

        Component2::Component2() {}
        Component2::~Component2() {}

        std::string const& Component2::getData() const
        { return _data; }

        void            Component2::setData(std::string const& data)
        { _data = data; }

        std::string     Component2::getName() const
        { return "Component2"; }

        ComponentMask   Component2::getMask() const
        { return mask; }

        IComponent*     Component2::clone() const
        { return new Component2(); }

        void            Component2::clear() {}

        std::string     Component2::toString() const
        { return "Component2 {" + _data + "}\n"; }

        /* Component3 */
        const ComponentMask   Component3::mask = Sample::COMPMASK_THREE;

        Component3::Component3() {}
        Component3::~Component3() {}

        std::string     Component3::getName() const
        { return "Component3"; }

        ComponentMask   Component3::getMask() const
        { return mask; }

        IComponent*     Component3::clone() const
        { return new Component3(); }

        void            Component3::clear() {}

        std::string     Component3::toString() const
        { return "Component3 {}\n"; }

        /* System1 */
        System1::System1() {}

        System1::~System1() {}

        void          System1::update() {}

        void          System1::processEntity(Entity& e)
        {
            Component1* c1 = e.getComponent<Component1>();
            Component2* c2 = e.getComponent<Component2>();

            if (c1 == NULL || c2 == NULL)
            return ;
            c1->setData("Tea est trop fort");
            c2->setData("Tea est trop swag");
        }

        ComponentMask System1::getMask() const
        { return (Component1::mask | Component2::mask); }

        std::string   System1::getName() const
        { return "System1"; }

        std::string   System1::toString() const
        { return "System1"; }

        bool          System1::shouldAutoUpdate() const
        { return true; }

        bool          System1::shouldAutoProcess() const
        { return true; }
    }
}
