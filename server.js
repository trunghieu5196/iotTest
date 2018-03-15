const express = require('express');
const http = require('http');

let app = express();

app.get('/', function(req,res){
  res.sendFile(__dirname + '/test.html');    // gửi file html lên máy
});
 var cors = require('cors');
 app.use(cors());
let server = http.Server(app);
server.listen(process.env.PORT || 80, function(){
  console.log("socket server connected...")
});

let io = require('socket.io')(server);       // khởi tạo thư viện socket.io

io.on('connection',function(socket){			// đoạn chương trình sẽ chạy khi có một kết nối đến server 
	console.log('socket connection');			// in ra màn hình để debug
	socket.on('Nut1',function(msg){				//nếu nhận một tin nhắm với mã là Nut1 thì sẽ xử lý tín hiệu msg
		socket.broadcast.emit('message','heloo arduino');
		console.log('ok web');
	});

	socket.on('Nut2',function(msg){
		socket.broadcast.emit('message1','heloo arduino');
		console.log('ok web');
	});

	socket.on('customEvent',function(msg){
		socket.emit('message','heloo arduino');
		console.log('ok arduino');
	});
})