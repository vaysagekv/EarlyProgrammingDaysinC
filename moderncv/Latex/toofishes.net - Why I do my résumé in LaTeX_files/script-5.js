// Local JS for toofishes.net

// Apply pretty-printing to code elements inside a pre tag
function makePretty() {
  $('pre > code').not('.notpretty').each(
    function(index) {
      $(this).parent().addClass('prettyprint');
      $(this).parent().addClass($(this).attr('class'));
    }
  );
  prettyPrint();
}

// Turn normal unordered list of tags into a tag cloud list
function makeTagCloud() {
  $('span.postcount').hide();
  var taglist = $('ul#taglist');
  taglist.hide();
  taglist.tagcloud({
      type: 'list', sizemax: 24, sizemin: 12,
      colormax: '5b0909', colormin: '7c7c7c'
  });
  taglist.addClass('tagcloud');
  taglist.removeAttr('style');
  taglist.children('li').each(
    function() {
      $(this).children('a').append(
          '&#8194;(' + this.getAttribute('value') + ')');
    }
  );
  taglist.show();
}
