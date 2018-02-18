--

function testGlobalFunction(id)
    log_debug("id -> " .. id)
    return true;
end

function __update__()
    log_debug("Scoped function work")
    return true
end

function testEntityManager()
    local id = createEntity()
    log_info("id -> " .. id)
    local ett = getEntity(id)
    local component = ett:getScriptComponent()
    --local name = component.scriptName
end

testTable = {
    onUpdate = __update__
}

return testTable