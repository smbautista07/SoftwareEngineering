


document.addEventListener('DOMContentLoaded', loadTools);

function loadTools()
{
    var canvas = document.getElementById("screen");
    var ctx = canvas.getContext("2d");
    //drawBackground();
    drawRect();
}
/*
function drawBackground()
{
    ctx.fillStyle="black";
    ctx.fillRect(0,0,canvas.width,canvas.height);
}
*/
function drawRect()
{
    cty = ctx;
    cty.fillStyle = "yellow";
    
    cty.fillRect(40, 30, 10, 200);
}



//document.addEventListener("DOMContentLoaded", loadTools());
