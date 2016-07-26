jQuery.extend( jQuery.fn.dataTableExt.oSort, {
	"my-number-pre": function ( num ) {
		num = num.split('\.').join('');
		return num * 1;
	},

	"my-number-asc": function ( a, b ) {
		return ((a < b) ? -1 : ((a > b) ? 1 : 0));
	},

	"my-number-desc": function ( a, b ) {
		return ((a < b) ? 1 : ((a > b) ? -1 : 0));
	}
} );