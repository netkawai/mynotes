/*
 * This is the rotation sript for the Companion Projects section
 *
 * we hase some limited number of static items whcih are displayed always and
 * the rest is rendered randomly
 */
function renderCompanionProjectIcons() {
  /* number of items we want to render */
  var itemsToRender = 3;

  /* domain where images live - we can easily switch for local testing to localhost to see images */
  var domain = "http://www.netbeans.org"; // http://localhost

  /* links output */
  var randomizedLinks = "";
  var staticLinks = "";

  /* items definition using JSON object notation */
  var staticItemsContainer = {
    "items" : [
    {
      "image": "/images_www/v6/mysql_logo.gif",
      "link": "http://www.mysql.com/",
      "alt": "MySQL - Open Source Database Server",
      "width": "53",
      "height": "45"
    },
    {
      "image": "/images_www/v6/glassfish.gif",
      "link": "https://glassfish.dev.java.net/",
      "alt": "GlassFish Community: an Open Source Application Server",
      "width": "53",
      "height": "45"
    },
    {
      "image": "/images_www/v6/opensolaris.gif",
      "link": "http://opensolaris.org/",
      "alt": "Open Solaris",
      "width": "48",
      "height": "45"
    },
    {
      "image": "/images_www/v6/projectkenai.gif",
      "link": "http://kenai.com/",
      "alt": "Project Kenai",
      "width": "106",
      "height": "45"
    }
    ]
  }
  var randItemsContainer = {
    "items" : [
    {
      "image": "/images_www/v6/javafx.png",
      "link": "http://javafx.com/",
      "alt": "JavaFX",
      "width": "74",
      "height": "26"
    },
    {
      "image": "/images_www/v6/mobile-duke.gif",
      "link": "http://community.java.net/mobileandembedded/",
      "alt": "Mobile & Embedded Community",
      "width": "42",
      "height": "45"
    },
    {
      "image": "/images_www/v6/openjdk.gif",
      "link": "https://openjdk.dev.java.net/",
      "alt": "Open JDK: an Open SourceJDK",
      "width": "81",
      "height": "45"
    },
    {
      "image": "/images_www/v6/vbox.gif",
      "link": "http://www.virtualbox.org/wiki/VirtualBox",
      "alt": "Virtual Box - full virtualizer",
      "width": "108",
      "height": "35"
    },

    {
      "image": "/images_www/v6/open-esb.gif",
      "link": "https://open-esb.dev.java.net/",
      "alt": "Open ESB - The Open Enterprise Service Bus",
      "width": "83",
      "height": "45"
    },

    {
      "image": "/images_www/v6/javanet.gif",
      "link": "http://www.java.net/",
      "alt": "Java.net - The Source for Java Technology Collaboration",
      "width": "82",
      "height": "45"
    },

    {
      "image": "/images_www/v6/open-office.gif",
      "link": "http://www.openoffice.org/",
      "alt": "OpenOffice - The free and open productivity suite",
      "width": "87",
      "height": "45"
    }
    ]
  };

  /* opening and closing html chunks */
  var openingHtml="<center><table><tr><td class=\"companions-left b-green-left valign-center\">Companion <br>Projects: </td><td  class=\"valign-center\">";
  var closingHtml="<td class=\"companions-right b-green-right valign-center align-center\">&nbsp;Sponsored&nbsp;by&nbsp;<br><a href=\"http://www.oracle.com/\"><img src=\""+domain+"/images_www/v6/logo_oracle_footer.gif\" width=\"100\" height=\"29\" alt=\"Sponsored by Oracle\" title=\"Sponsored by Oracle\"></a></td></tr></table></center>";

  /* let's stup the sttaic links */
  for (i=0; i<staticItemsContainer.items.length; i++) {
    staticLinks += '<td class="valign-center"><a href="'+staticItemsContainer.items[i].link+'"><img src="'+domain+staticItemsContainer.items[i].image+'" alt="'+staticItemsContainer.items[i].alt+'" title="'+staticItemsContainer.items[i].alt+'" width="'+staticItemsContainer.items[i].width+'" height="'+staticItemsContainer.items[i].height+'"></a>&nbsp;&nbsp;</td>';
  }

  /* now randomize the rand items array */
  randItemsContainer.items.sort(function() {
    return (Math.round(Math.random())-0.5)
  });

  /* make sure we do not want to display more items then we actually have */
  itemsToRender = (itemsToRender > randItemsContainer.items.length)? randItemsContainer.items.length : itemsToRender ;

  /* now setup randomized items */
  for (i = 0; i < itemsToRender; i++) {
    // setup the style - there is line after the last item
    var style = (i==(itemsToRender-1))? 'class="valign-center b-green-right" style="padding-right:10px;"' : 'class="valign-center"' ;
    var space = (i==(itemsToRender-1))? '' : '&nbsp;';
    randomizedLinks += '<td '+style+'><a href="'+randItemsContainer.items[i].link+'"><img src="'+domain+randItemsContainer.items[i].image+'" alt="'+randItemsContainer.items[i].alt+'" title="'+randItemsContainer.items[i].alt+'" width="'+randItemsContainer.items[i].width+'" height="'+randItemsContainer.items[i].height+'"></a>'+space+'</td>';
  }
  
  /* return the html */
  return openingHtml+staticLinks+randomizedLinks+closingHtml;
}

/**
* function which renders randomly 2 links to the Sun Support Program pane in kb/rcol
*/
function renderRandomSupportLinks() {
  // JSON objects holding links and urls for the rendering
  var links={
    "items":[
    {
      "link":"Oracle Development Tools Support Offering for NetBeans IDE",
      "url":"http://www.oracle.com/us/support/development-tools-080025.html"
    }
    ]
  };

  // setup rand counter
  var rand1 = Math.floor(Math.random() * links.items.length);
  /*var rand2 = rand1;
  do {
    rand2 = Math.floor(Math.random() * links.items.length);
  }
  while(rand1 == rand2)
 */

  // now render the links according to rand counters
  document.write("<div class=\"rrrarticle\"><div class=\"rarticletitle\"><a href=\""+links.items[rand1].url+"\">"+links.items[rand1].link+"</a></div></div>");
  //document.write("<div class=\"rrrarticle\"><div class=\"rarticletitle\"><a href=\""+links.items[rand2].url+"\">"+links.items[rand2].link+"</a></div></div>");
}


/*
 * We need to display custom nav column on project pages,
 * so do taht by ajax from their /nav-col.html
 *
 * This will be run only for particular domains
 */
var navColLocation='/nav-col.nav';
var topNavLocation='/top-nav.nav';
var jQueryLocation='http://netbeans.org/images_www/js/jquery-1.3.2.min.js';
var navColSelector='#col-right-context';

function showCustomNavCol() {
  // hide the nav element so it does not appear at all at the beginning
  document.write('<style>'+navColSelector+', #floating-col-right div:nth-child(2) {display:none;}</style>')
  // check for jQuery
  if (typeof jQuery == 'undefined') {
    document.write('<script type="text/javascript" src="'+jQueryLocation+'"></script>');
  }
  if(jQuery) {
    // do the magic using ajax - load content of /nav-col.html into <div id="col-right-context">
    $(function(){
      // drop junction content
      $(navColSelector).html('');
      // drop also Navidation pane
      $('#floating-col-right div:nth-child(2)').hide();
      // load nav-col
      $.get(navColLocation, function(data){
        $(navColSelector).html(data).slideDown();
      });
    });
  }
}

function showCustomTopCol() {
   if (typeof jQuery == 'undefined') {
    document.write('<script type="text/javascript" src="'+jQueryLocation+'"></script>');
  }
  if(jQuery) {
     $(function(){
        $.get(topNavLocation, function(data){
        $('table.colapse.full-width.f-page-table-2col tr:first').before(data);
        });
     });
  }
}
// DO IT
if(window.location.toString().match(/^http:\/\/platform\.netbeans\.org\//)) {
  document.write('<link rel="stylesheet" type="text/css" href="http://netbeans.org/platform.css"/>');
  showCustomNavCol();
  showCustomTopCol();
} else if(window.location.toString().match(/^http:\/\/localhost\//)) {
  //document.write('<link rel="stylesheet" type="text/css" href="http://netbeans.org/platform.css"/>');
  //showCustomNavCol();
  //showCustomTopCol();
} else if(window.location.toString().match(/^http:\/\/edu\.netbeans\.org\//)) {
  showCustomNavCol();
}


