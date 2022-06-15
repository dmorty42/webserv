var Wow = function() {
    "use strict";

    var handleWow = function() {
        var wow = new WOW({
		    boxClass:     'wow',
		    offset:       0,
		    mobile:       false,
		    tablet:       false
		});
		wow.init();
    }

    return {
        init: function() {
            handleWow();
        }
    }
}();

$(document).ready(function() {
    Wow.init();
});