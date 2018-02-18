--

function update_internal()
    print("salut" .. "lol")
end

playerTable = 
{
    onUpdate = update_internal
}

return playerTable;