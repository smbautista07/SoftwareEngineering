"use strict";

class inputHandler
{
    static #inputs = new Set();

    static getInputs()
    {
        return this.#inputs;
    }
    
    static checkKey(key)
    {
        return this.#inputs.has(key);
    }

    static addToSet(value)
    {
        this.#inputs.add(value);
    }
    static removeFromSet(value)
    {
        this.#inputs.delete(value);
    }

    static updateInputs(event)
    {
        (event.type == "keydown") ? inputHandler.addToSet(event.code):inputHandler.removeFromSet(event.code);
    }
}

document.addEventListener("keydown", inputHandler.updateInputs);
document.addEventListener("keyup", inputHandler.updateInputs);

class rectObj
{
    constructor(x, y, width = 0, height = 0)
    {
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
        this.xSpeed;
        this.ySpeed;
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
        if (this.x > 960-this.width || this.x < 0)
        {
            this.xSpeed *= -1;
        }
        if (this.y >540-this.height || this.y < 0)
        {
            this.ySpeed *= -1;
        }
    }
}

class paddle extends rectObj
{
    constructor(x, y, width = 0, height = 0, up_in, down_in)
    {
        super(x, y, width, height);
        this.up = up_in;
        this.down = down_in;
    }

    move(y_in)
    {
        this.y += y_in;
    }

    update()
    {
        this.yPrev = this.y
        // console.log(inputHandler.getInputs())
        if (inputHandler.checkKey(this.up))
        {
            this.ySpeed = -5;
        }
        else if (inputHandler.checkKey(this.down))
        {
            this.ySpeed = 5;
        }
        else
        {
            this.ySpeed = 0;
        }

        this.y += this.ySpeed;
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

const leftPaddle = new paddle(40, 270, 10, 100, "KeyW", "KeyS");
const rightPaddle = new paddle(960-40-10, 270, 10, 100, "ArrowUp", "ArrowDown");

ctx.fillStyle = "yellow";
ctx.fillRect(wall.x, wall.y, wall.width, wall.height);

render();
function render()   
{
    ctx.fillStyle = "yellow";
<<<<<<< Updated upstream
<<<<<<< Updated upstream
    ctx.clearRect(ball.xPrev, ball.yPrev, ball.width,ball.height)
    ctx.fillRect(ball.x,ball.y,ball.width,ball.height);

    ctx.clearRect(leftPaddle.x,leftPaddle.yPrev,leftPaddle.width,leftPaddle.height);
    ctx.fillRect(leftPaddle.x,leftPaddle.y,leftPaddle.width,leftPaddle.height);

    ctx.clearRect(rightPaddle.x,rightPaddle.yPrev,rightPaddle.width,rightPaddle.height);
    ctx.fillRect(rightPaddle.x,rightPaddle.y,rightPaddle.width,rightPaddle.height);
=======
    ctx.clearRect(ball.xPrev, ball.yPrev, ball.width,ball.height);
    ctx.fillRect(ball.x,ball.y,ball.width,ball.height); //on rewrite make a method
>>>>>>> Stashed changes
=======
    ctx.clearRect(ball.xPrev, ball.yPrev, ball.width,ball.height);
    ctx.fillRect(ball.x,ball.y,ball.width,ball.height); //on rewrite make a method
>>>>>>> Stashed changes
}

var contactFlag = false;

function update()
{
    //currentInputs = inputHandler.

    ball.update();
    if (ball.isCollidingWith(wall))
    {
        ball.xSpeed*=-1;
        ball.ySpeed*=-1;
    }

    if (ball.isCollidingWith(leftPaddle))
    {
        if (!contactFlag)
        {
            ball.xSpeed = 5;
            ball.ySpeed += leftPaddle.ySpeed;
        }
        contactFlag = true;
    }
    else if (ball.isCollidingWith(rightPaddle))
    {
        if (!contactFlag)
        {
            ball.xSpeed = -5;
            ball.ySpeed += rightPaddle.ySpeed;
        }
        contactFlag = true;
    }
    else 
    {
        contactFlag = false;
    }

<<<<<<< Updated upstream
    leftPaddle.update();
    rightPaddle.update();
=======
    //console.log("update!");
    // if (ball.hasOwn("xSpeed"))
    // {
    //     console.log("W");
    // }
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
    // console.log(inputHandler.getInputs());

    render();
}


setInterval(update,10);

//document.addEventListener("DOMContentLoaded", loadTools());