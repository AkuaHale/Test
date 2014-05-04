function HomeWindow(title) {
	GoogleLoginWindow = require('ui/handheld/GoogleLoginWindow');
	FacebookLoginWindow = require('ui/handheld/FacebookLoginWindow');
	JoinBlubbleWindow = require('ui/handheld/JoinBlubbleWindow');
	CreateBlubbleWindow = require('ui/handheld/CreateBlubbleWindow');
	
	var self = Ti.UI.createWindow({
		title:title,
		backgroundColor:'#5e9268',
		layout:'vertical'
	});
		
	var body = Ti.UI.createView({height:Ti.UI.SIZE, 
		layout:'vertical', 
		center:0});
	
	var bodyView1 = Ti.UI.createView({center:0,
	top:20,
	layout:'vertical'});
	body.add(bodyView1);
	
	self.add(body);
	
	var headerLabel = Ti.UI.createLabel({text:'Photo Blubble',
	center:0,
	font:{fontFamily:'Papyrus',fontSize:30,fontWeight:'bold'},
	color:'#0b5401'});
	bodyView1.add(headerLabel);
	
	var photoBubbleUser = Ti.App.Properties.getString('PhotoBubbleUserName');
	var greetingLabel = Ti.UI.createLabel({text:'Welcome '+photoBubbleUser,
	center:0,
	font:{fontFamily:'Copperplate',fontSize:18,fontWeight:'regular'},
	color:'#0b5401'});
	bodyView1.add(greetingLabel);

	var createBlubbleButton = Ti.UI.createButton({title:'Create a Blubble',
	center:0,
	top:40,
	height:25,
	width:200,
	backgroundColor:'#0b5401',
	color:'white',
	borderRadius:3,
	font:{fontFamily:'Copperplate',fontSize:14,fontWeight:'regular'}});

	createBlubbleButton.addEventListener('click', function(e){
		var createBlubbleWindow = new CreateBlubbleWindow({title:"Create a Blubble",
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
			createBlubbleWindow.animate({transform:t2, duration:200});
		});

		createBlubbleWindow.open(a);
		});	
		
	bodyView1.add(createBlubbleButton);

	var joinBlubbleButton = Ti.UI.createButton({title:'Join a Blubble',
	center:0,
	top:10,
	height:25,
	width:200,
	backgroundColor:'#0b5401',
	color:'white',
	borderRadius:3,
	font:{fontFamily:'Copperplate',fontSize:14,fontWeight:'regular'}});

	bodyView1.add(createBlubbleButton);

	joinBlubbleButton.addEventListener('click', function(e){
		var joinBlubbleWindow = new JoinBlubbleWindow({title:"Join a Blubble",
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
			joinBlubbleWindow.animate({transform:t2, duration:200});
		});

		joinBlubbleWindow.open(a);
		});	
		
	bodyView1.add(joinBlubbleButton);

	var googleLoginButton = Ti.UI.createButton({title:'Google',
	center:0,
	top:10,
	height:25,
	width:200,
	backgroundColor:'#0b5401',
	color:'white',
	borderRadius:3,
	font:{fontFamily:'Copperplate',fontSize:14,fontWeight:'regular'}});

	googleLoginButton.addEventListener('click', function(e){
		var googleLoginWindow = new GoogleLoginWindow({title:"Google Login",
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
			googleLoginWindow.animate({transform:t2, duration:200});
		});

		googleLoginWindow.open(a);
		});

	bodyView1.add(googleLoginButton);

	var facebookLoginButton = Ti.UI.createButton({title:'Facebook',
	center:0,
	top:5,
	height:25,
	width:200,
	backgroundColor:'#0b5401',
	color:'white',
	borderRadius:3,
	font:{fontFamily:'Copperplate',fontSize:14,fontWeight:'regular'}});

	facebookLoginButton.addEventListener('click', function(e){
		var facebookLoginWindow = new FacebookLoginWindow({title:"Facebook Login",
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
			facebookLoginWindow.animate({transform:t2, duration:200});
		});

		facebookLoginWindow.open(a);
		});

	bodyView1.add(facebookLoginButton);
	
	var unregisterButton = Ti.UI.createButton({title:'Unregister',
	center:0,
	top:5,
	height:25,
	width:200,
	backgroundColor:'#0b5401',
	color:'white',
	borderRadius:3,
	font:{fontFamily:'Copperplate',fontSize:14,fontWeight:'regular'}});

	unregisterButton.addEventListener('click', function(e){
		var t3 = Titanium.UI.create2DMatrix();
		t3 = t3.scale(0);
		self.close({transform:t3,duration:300});
		});

	bodyView1.add(unregisterButton);
	
	return self;
};

module.exports = HomeWindow;
