/**
 * @file
 * Attaches behaviors for the Link Checker module.
 */
(function ($) {

Backdrop.behaviors.linkcheckerFieldsetSummaries = {
  attach: function (context) {
    // Provide the vertical tab summaries.
    $('fieldset#edit-linkchecker', context).backdropSetSummary(function(context) {
      var vals = [];
      $('input:checked', context).next('label').each(function() {
        vals.push(Backdrop.checkPlain($(this).text()));
      });
      if (!vals.length) {
        return Backdrop.t('Disabled');
      }
      return vals.join(', ');
    });
  }
};

})(jQuery);
