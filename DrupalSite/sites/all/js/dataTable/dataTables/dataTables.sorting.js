/* Create an array with the values of all the input boxes in a column */
$.fn.dataTableExt.afnSortData['dom-text'] = function(oSettings, iColumn) {
	var aData = [];
	$('td:eq(' + iColumn + ') input', oSettings.oApi._fnGetTrNodes(oSettings)).each(function() {
		aData.push(this.value);
	});
	return aData;
};

/* Create an array with the values of all the select options in a column */
$.fn.dataTableExt.afnSortData['dom-select'] = function(oSettings, iColumn) {
	var aData = [];
	$('td:eq(' + iColumn + ') select', oSettings.oApi._fnGetTrNodes(oSettings)).each(function() {
		aData.push($(this).val());
	});
	return aData;
};

/* Create an array with the values of all the checkboxes in a column */
$.fn.dataTableExt.afnSortData['dom-checkbox'] = function(oSettings, iColumn) {
	var aData = [];
	$('td:eq(' + iColumn + ') input', oSettings.oApi._fnGetTrNodes(oSettings)).each(function() {
		aData.push(this.checked == false ? "1" : "0");
	});
	return aData;
};

/* Percentage format sorting */
jQuery.fn.dataTableExt.oSort['percent-asc']  = function(a,b) {
    var x = (a == "-") ? 0 : a.replace( /%/, "" );
    var y = (b == "-") ? 0 : b.replace( /%/, "" );
    x = parseFloat( x );
    y = parseFloat( y );
    return ((x < y) ? -1 : ((x > y) ?  1 : 0));
};
 
jQuery.fn.dataTableExt.oSort['percent-desc'] = function(a,b) {
    var x = (a == "-") ? 0 : a.replace( /%/, "" );
    var y = (b == "-") ? 0 : b.replace( /%/, "" );
    x = parseFloat( x );
    y = parseFloat( y );
    return ((x < y) ?  1 : ((x > y) ? -1 : 0));
};

/* Date sorting (format: dd/mm/YYY hh:ii:ss)*/
jQuery.extend( jQuery.fn.dataTableExt.oSort, {
    "date-euro-pre": function ( a ) {
        if ($.trim(a) != '') {
            var frDatea = $.trim(a).split(' ');
            //var frTimea = frDatea[1].split(':');
            var frDatea2 = frDatea[0].split('/');
            var x = (frDatea2[2] + frDatea2[1] + frDatea2[0]) * 1; // + frTimea[0] + frTimea[1] + frTimea[2]
        } else {
            var x = 10000000000000;
        }
         
        return x;
    },
 
    "date-euro-asc": function ( a, b ) {
        return a - b;
    },
 
    "date-euro-desc": function ( a, b ) {
        return b - a;
    }
} );