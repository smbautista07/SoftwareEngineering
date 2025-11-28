"use strict";

class rectObj
{
    constructor(x, y, width = 0, height = 0)
    {
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
    }
}

class rectCollider extends rectObj
{
    constructor(x, y, width, height)
    {
        super(x,y,width, height);
    }
    
    isCollidingWith(otherObj)
    {
        let xLeft = this.x;
        let xRight = this.x+this.width; //may need to use trig for rotated shapes.
        let yTop = this.y; //same for this
        let yBottom = this.y + this.height;
        let theirXLeft = otherObj.x;
        let theirXRight = otherObj.x+otherObj.width;
        let theirYTop = otherObj.y;
        let theirYBottom = otherObj.y+otherObj.height; 
            // if (xRight< theirXLeft)
            // {
            //     console.log("ball is to the left");
            // }
            // if (xLeft > theirXRight)
            // {
            //     console.log("ball is to the right");
            // }
            if (xRight >= theirXLeft && xLeft <= theirXRight)
            {
                // console.log("ball is x aligned");
                if (yTop <= theirYBottom && yBottom >= theirYTop) // y axis aligned
                {
                    return true;
                }
            }
            


            
        // if (xLeft < theirXRight || xRight > theirXLeft) //x axis aligned
        // {
        //         console.log("x axis aligned");
        //     if (yTop < theirYBottom || yBottom > theirYTop) // y axis aligned
        //     {
        //         console.log("COLLIDING");
        //     }
        // }
    }
}

class pongBall extends rectCollider
{
    constructor()
    {
        super(20,20,20,20)
        this.xSpeed = 5;
        this.ySpeed = 5;
        this.xPrev;
        this.yPrev;
    }
    
    update()
    {
        this.xPrev = this.x;
        this.yPrev = this.y;   
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

document.addEventListener('DOMContentLoaded', start);

const para = document.createElement('p');
const words = document.createTextNode("Hi");

para.appendChild(words);
const paragraph = document.getElementById("oops");
// document.body.insertBefore(para,paragraph);

document.body.appendChild(para);
// var canvas = document.getElementById("screen");
var canvas = document.createElement("canvas"); 
canvas.width = 960;
canvas.height = 540;
canvas.id = "screen";
document.body.insertBefore(canvas,paragraph);

var ctx = canvas.getContext("2d");

function start()
{
    
}
/*
function drawBackground()
{
    ctx.fillStyle="black";
    ctx.fillRect(0,0,canvas.width,canvas.height);
}
*/



const ball = new pongBall();
const wall = new rectCollider(480,0,30,240);
ctx.fillStyle = "yellow";
ctx.fillRect(wall.x, wall.y, wall.width, wall.height);

render();
function render()   
{
    ctx.fillStyle = "yellow";
    ctx.clearRect(ball.xPrev, ball.yPrev, ball.width,ball.height)
    ctx.fillRect(ball.x,ball.y,ball.width,ball.height);
}

function update()
{
    ball.update();
    if (ball.isCollidingWith(wall))
    {
        ball.xSpeed*=-1;
        ball.ySpeed*=-1;
        
    }
    //console.log("update!");
    render();
}


setInterval(update,10)

//document.addEventListener("DOMContentLoaded", loadTools());
