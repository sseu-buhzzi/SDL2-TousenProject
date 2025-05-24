const PADDING = 16;
const BLOCK = 256;
const GAP = 64;

function wuej(b, g) {
    return (b ?? 0) * BLOCK + (g ?? 0) * GAP + PADDING;
}
function cziuh(b, g) {
    return (b ?? 0) * BLOCK + (g ?? 0) * GAP;
}
function czeau(i) {
    return Math.PI * i * 0.5;
}

var canvas = document.querySelector("canvas");
var context = canvas.getContext("2d");

canvas.width = cziuh(8, 7) + PADDING * 2;
canvas.height = cziuh(3, 2) + PADDING * 2;

context.fillStyle = "#000000";
context.fillRect(0, 0, canvas.width, canvas.height);

let grad = context.createRadialGradient(wuej(4, 3.5), wuej(-4), cziuh(16), wuej(5, 4.5), wuej(4), cziuh(1));
grad.addColorStop(0.875, "#ff4040");
grad.addColorStop(1, "#ffff40");
context.fillStyle = grad;
context.strokeStyle = "#ffffff";
context.lineWidth = 16;
context.beginPath();
context.arc(wuej(1), wuej(1), cziuh(1), czeau(3), czeau(2), true);
context.arc(wuej(1), wuej(1, 1), cziuh(1), czeau(2), czeau(1), true);
context.arc(wuej(1, 0.5), wuej(2, 1.5), cziuh(0, 0.5), czeau(3), czeau(1), false);
context.lineTo(wuej(), wuej(2, 2));
context.lineTo(wuej(), wuej(3, 2));
context.arc(wuej(3, 3), wuej(2, 2), cziuh(1), czeau(1), czeau(0), true);
context.arc(wuej(3, 3), wuej(2, 1), cziuh(1), czeau(0), czeau(3), true);
context.arc(wuej(3, 2.5), wuej(1, 0.5), cziuh(0, 0.5), czeau(1), czeau(3), false);
context.lineTo(wuej(6, 6), wuej(1));
context.arc(wuej(7, 6), wuej(2, 2), cziuh(1), czeau(2), czeau(1), true);
context.arc(wuej(7, 7), wuej(2, 2), cziuh(1), czeau(1), czeau(0), true);
context.lineTo(wuej(8, 7), wuej());
context.lineTo(wuej(7, 7), wuej());
context.arc(wuej(7, 6.5), wuej(2, 1.5), cziuh(0, 0.5), czeau(0), czeau(2), false);
context.lineTo(wuej(7, 6), wuej());
context.closePath();
context.fill();
context.stroke();

context.beginPath();
context.moveTo(wuej(4, 4), wuej(1, 1));
context.lineTo(wuej(4, 4), wuej(2, 1));
context.lineTo(wuej(6, 5), wuej(2, 1));
context.lineTo(wuej(6, 5), wuej(1, 1));
context.closePath();
context.fill();
context.stroke();

context.beginPath();
context.moveTo(wuej(4, 4), wuej(2, 2));
context.lineTo(wuej(4, 4), wuej(3, 2));
context.lineTo(wuej(6, 5), wuej(3, 2));
context.lineTo(wuej(6, 5), wuej(2, 2));
context.closePath();
context.fill();
context.stroke();

context.fillStyle = "#000000";
context.beginPath();
context.arc(wuej(1, 0.5), wuej(1, 0.5), cziuh(0, 0.5), czeau(3), czeau(1), true);
context.arc(wuej(1, 1), wuej(2, 1), cziuh(1), czeau(3), czeau(0), false);
context.lineTo(wuej(2, 1), wuej(2, 2));
context.arc(wuej(3, 2.5), wuej(2, 1.5), cziuh(0, 0.5), czeau(1), czeau(3), true);
context.arc(wuej(3, 2), wuej(1, 1), cziuh(1), czeau(1), czeau(2), false);
context.lineTo(wuej(2, 2), wuej(1));
context.closePath();
context.fill();
context.stroke();
