var canvas = document.createElement("canvas", {width : "960", height : "540"});
var ctx = canvas.getContext("2d");

document.body.appendChild(canvas);

ctx.fillRect(50,50,50,50);

setInterval(update,10);

var size = 1

function update()
{
    // ctx.fillRect(size,size,size,size);
    // size+=1;

    document.addEventListener("keydown", output);
    

    

}

function output(e)
{
    console.log(e.key);
}
