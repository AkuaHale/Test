function JoinBlubbleWindow(title) {		
	var self = Ti.UI.createWindow({
		title:title,
		backgroundColor:'#5e9268',
		borderWidth:8,
		borderColor:'#999',
		top:150,
		height:200,
		width:300,
		borderRadius:10,
		opacity:1,
		transform:t,
		layout:'vertical'
	});
		
	var t = Titanium.UI.create2DMatrix();
	t = t.scale(0);	

	var body = Ti.UI.createView({height:Ti.UI.SIZE, 
		layout:'vertical', 
		center:0});
	
	var bodyView1 = Ti.UI.createView({center:0,
	top:10,
	layout:'vertical'});
	body.add(bodyView1);
	
	self.add(body);
	
	var headerLabel = Ti.UI.createLabel({text:'Join a Blubble',
	center:0,
	font:{fontFamily:'Papyrus',fontSize:30,fontWeight:'bold'},
	color:'#0b5401'});
	bodyView1.add(headerLabel);
	
	var userNameTextBox = Ti.UI.createTextField({hintText:'User Name',
	center:0,
	top:10,
	borderColor:'black',
	backgroundColor:'white',
	height:25,
	width:'80%',
	textAlign:'center',
	font:{fontFamily:'Calibri',fontSize:14,fontWeight:'regular'}});
	bodyView1.add(userNameTextBox);
	
	var passwordTextBox = Ti.UI.createTextField({hintText:'Password',
	passwordMask:true,
	center:0,
	top:5,
	borderColor:'black',
	backgroundColor:'white',
	height:25,
	width:'80%',
	textAlign:'center',
	font:{fontFamily:'Calibri',fontSize:14,fontWeight:'regular'}});
	bodyView1.add(passwordTextBox);

	var loginButton = Ti.UI.createButton({title:'Login',
	center:0,
	top:10,
	height:25,
	width:200,
	backgroundColor:'#0b5401',
	color:'white',
	borderRadius:3,
	font:{fontFamily:'Copperplate',fontSize:14,fontWeight:'regular'}});
	bodyView1.add(loginButton);

	loginButton.addEventListener('click', function(e){
		var t3 = Titanium.UI.create2DMatrix();
		t3 = t3.scale(0);
		self.close({transform:t3,duration:300});
		});

	return self;
};

module.exports = JoinBlubbleWindow;