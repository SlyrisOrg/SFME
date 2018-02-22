--

function testGlobalFunction(id)
    log_debug("id -> " .. id)
    return true;
end

function __update__()
    log_debug("Scoped function work")
    return true
end

function testCreateEntity()
    local id = entityManager:createEntity()
    return id
end

function testGetEntity(id)
    return entityManager:getEntity(id)
end

function testEntityManager()
    local id = testCreateEntity();    
    local ett = testGetEntity(id)
    local componentPV = ett:addPVComponent()
    componentPV.pv = 42
    log_debug("nbentities: " .. entityManager:nbEntities())
    return id, componentPV.pv
end

function testGetEntityWithSpecificComponents()
    -- body
    for i=1, 25 do
        local id = entityManager:createEntity()
        local entity = entityManager:getEntity(id)
        local componentPV = entity:addPVComponent()
        componentPV.pv = i
    end
    
    assert(entityManager:getEntityWithPVComponent():size() == 25)
    
    for i=1,10 do
        local id = entityManager:createEntity()
        local entity = entityManager:getEntity(id)
        local componentPV = entity:addPVComponent()
        local componentMana = entity:addManaComponent()
    end

    assert(entityManager:getEntitiesWithComponents("PV", "Mana"):size() == 10)
end

function testClearEntities()
    if entityManager:nbEntities() == 1 then
        entityManager:clear()
        log_info("nbentities: " .. entityManager:nbEntities())
    end
end 

function testKeyboard(Key)
    assert(Key == Keyboard.B, "Wrong Key")
end

testTable = {
    onUpdate = __update__
}

return testTable