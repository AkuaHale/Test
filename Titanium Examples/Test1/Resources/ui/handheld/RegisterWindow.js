function RegisterWindow(title) {
	HomeWindow = require('ui/handheld/HomeWindow');
	
	var self = Ti.UI.createWindow({
		title:title,
		backgroundColor:'#5e9268',
		layout:'vertical'
	});
		
	var body = Ti.UI.createView({height:Ti.UI.SIZE, 
		layout:'vertical', 
		center:0});
	
	var bodyView1 = Ti.UI.createView({center:0,
	top:150,
	layout:'vertical'});
	body.add(bodyView1);
	
	self.add(body);
	
	var headerLabel = Ti.UI.createLabel({text:'Photo Blubble',
	center:0,
	height:30,
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

	var registerButton = Ti.UI.createButton({title:'Register',
	center:0,
	top:10,
	height:25,
	width:200,
	backgroundColor:'#0b5401',
	color:'white',
	borderRadius:3,
	font:{fontFamily:'Copperplate',fontSize:14,fontWeight:'regular'}});

	registerButton.addEventListener('click', function(e){
		
		Ti.App.Properties.setString('PhotoBubbleUserName', userNameTextBox.value);
		
		var homeWindow = new HomeWindow({title:"Home",
		modal:true});

		// create first transform to go beyond normal size
		var t1 = Titanium.UI.create2DMatrix();
		t1 = t1.scale(1.1);
		var a = Titanium.UI.createAnimation();
		a.transform = t1;
		a.duration = 200;
	
		// when this animation completes, scale to normal size
		a.addEventListener('complete', function()
		{
			Titanium.API.info('here in complete');
			var t2 = Titanium.UI.create2DMatrix();
			t2 = t2.scale(1.0);
			homeWindow.animate({transform:t2, duration:200});
		});

		homeWindow.open(a);
		});

	bodyView1.add(registerButton);

	return self;
};

module.exports = RegisterWindow;
