class pongBall
{
    constructor(width, height)
    {
        this.x = 0;
        this.y = 0;
        this.xSpeed = 10;
        this.ySpeed = 10;
        this.width = width;
        this.height = height;
    }
    
    update()
    {
        this.x += this.xSpeed;
        this.y += this.ySpeed;
        if (this.x > 960 || this.x < 0)
        {
            this.xSpeed *= -1;
        }
        if (this.y >540 || this.y < 0)
        {
            this.ySpeed *= -1;
        }
    }
}


document.addEventListener('DOMContentLoaded', loadTools);

var canvas = document.getElementById("screen");
var ctx = canvas.getContext("2d");



function loadTools()
{
    //drawBackground();
    //drawRect();
    
}
/*
function drawBackground()
{
    ctx.fillStyle="black";
    ctx.fillRect(0,0,canvas.width,canvas.height);
}
*/



const ball = new pongBall(20,20);
render();
function render()
{
    ctx.fillStyle = "yellow";
    ctx.fillRect(ball.x,ball.y,ball.width,ball.height);
}

function update()
{
    ball.update();
    console.log("update!");
    render();
}


setInterval(update,10)

//document.addEventListener("DOMContentLoaded", loadTools());
