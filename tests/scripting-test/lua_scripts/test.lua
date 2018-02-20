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
    --print("TEST " .. entityManager:nbEntities())
    --entityManager:createEntity()
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
    for i=0, 25 do
        local id = entityManager:createEntity()
        local entity = entityManager:getEntity(id)
        local componentPV = entity:addPVComponent()
        componentPV.pv = i
    end
    
    for _, go in ipairs(EntityManager:getEntityWithPVComponent()) do
        log_info("pv : " .. go:getPVComponent().pv)
    end
end

function testClearEntities()
    if entityManager:nbEntities() == 1 then
        entityManager:clear()
        log_info("nbentities: " .. entityManager:nbEntities())
    end
end 

testTable = {
    onUpdate = __update__
}

return testTable