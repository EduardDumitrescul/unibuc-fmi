const express = require("express");
const app = express();
const port = 3000;

app.use(express.static(__dirname));

app.get("/action", function(req, res) {
    let arr = req.query.text.split(";");
    let ok = true;
    for(let it of arr) {
        if(parseInt(it).toString() != it)
            ok = false;
    }
    if(ok == false) {
        res.send("Date Invalide");
    }
    else {
        arr.sort(function(a, b){return parseInt(a) - parseInt(b)});
        if(req.query.radio == "descrescator")
            arr.reverse();
        console.log(req.query);
        res.send(arr.join(";"));
    }
})

app.listen(port, function() {
    console.log("Port " + port);
})