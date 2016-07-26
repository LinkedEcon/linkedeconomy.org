function convertToCurrencyFormat(amountStr, currencySymbol)
{
	var largeNumberSymbols		= ["", "K", "M", "B", "T"];
	currencySymbol				= typeof currencySymbol !== 'undefined' ? currencySymbol : "$";
	var decimalDigits			= 2;
	var amount					= parseFloat(amountStr);

	for (var i = 0; amount > 1000.0 && i < largeNumberSymbols.length - 1; ++i)
		{ amount				/= 1000.0; }
	var intValue				= Math.floor(amount);
	
	var decimalMultiplier		= Math.pow(10, decimalDigits);
	amount						*= decimalMultiplier;
	var decimalValue			= Math.floor(amount) % decimalMultiplier;
	
	var decimalValueStr			= "";
	decimalMultiplier			/= 10;
	while (decimalMultiplier >= 1) {
		var tmp					= Math.floor(decimalValue / decimalMultiplier);
		decimalValueStr			+= tmp;
		decimalValue			-= tmp * decimalMultiplier;
		decimalMultiplier		/= 10;
	}
	
	return currencySymbol + intValue + "." + decimalValueStr + largeNumberSymbols[i];
}
function prepare(dataString, index)
{
	var retval		= "";
	
	if (dataString !== undefined) {
		retval		= dataString.substr(0, index);
		if (dataString.length > index)
			retval	+= "...";
	}
		
	return retval;
}
function prepareCPV(dataString)
	{ return prepare(dataString, 15); }
function prepareDescription(dataString)
	{ return prepare(dataString, 47); }
function prepareName(dataString)
	{ return prepare(dataString, 57); }
function addCommas(input)
{
	//If the regex doesn't match, `replace` returns the string unmodified
	return (input.toString()).replace(
		//Each parentheses group (or 'capture') in this regex becomes an argument 
		//to the function; in this case, every argument after 'match'
		/^([-+]?)(0?)(\d+)(.?)(\d+)$/g,
		function(match, sign, zeros, before, decimal, after)
		{
			//Less obtrusive than adding 'reverse' method on all strings
			var reverseString = function(string)
				{ return string.split('').reverse().join(''); };
	 
			//Insert commas every three characters from the right
			var insertCommas = function(string)
			{
				//Reverse, because it's easier to do things from the left
				var reversed = reverseString(string);
	 
				//Add commas every three characters
				var reversedWithCommas = reversed.match(/.{1,3}/g).join('.');
	 
				//Reverse again (back to normal)
				return reverseString(reversedWithCommas);
			};

			//If there was no decimal, the last capture grabs the final digit, so
			//we have to put it back together with the 'before' substring
			return	sign +
					(
						decimal									?
						insertCommas(before) + decimal + after	:
						insertCommas(before + after)
					);
		});
};
function addDetails(value, userdata)
{
	var tblRowUserdata1 = "<tr>" + "<td style=\" text-align:center; border-left: 0px solid #ccc; font-size:15px; padding-right:0px;  width:140px;\">" + value + ""+ "<td style=\"border:0px solid #fff; box-shadow: 0 0px 0px #fff;  width:0px;\">" + "" + "";
	$(tblRowUserdata1).appendTo(userdata);
}
function addDetails2(dataParent, ref, totalWidth, name, detailValues, userdata)
{
	detailValues.forEach(function(detailValue)
		{ totalWidth	-= detailValue[1]; }
	);
	var tblUserData		= "<a class='accordion-toggle' data-toggle='collapse' data-parent='" + dataParent + "' href='" + ref + "' style='float:left; width:" + totalWidth + "px;'>" + name + "</a>"
						+ "<table border='0px' class='example'>"
						+ "<thead>"
						+ "<tr>";
	detailValues.forEach(function(detailValue)
		{ tblUserData	+= "<th style='border: 0px; text-align: center; width:" + detailValue[1] + "px;'>" + detailValue[0] + "</th>"; }
	);
	tblUserData			+= "</tr>"
						+ "</thead>"
						+ "<tbody>"
						+ "<tr></tr>"
						+ "<tr>";
	detailValues.forEach(function(detailValue) {
		tblUserData		+=	"<td class='accordion-table' style='text-align:center; border: 0px; border-left: 0px solid #ccc; font-size:15px; padding-right:0px; width:" + detailValue[1] + "px;'>"
						+		detailValue[2]
						+	"</td>";
	});
	tblUserData			+= "</tr>"
						+ "</tbody>"
						+ "</table>";
	$(tblUserData).appendTo(userdata);
}
function addContractDetails(stats, userdata, currencySymbol)
{
	currencySymbol		= typeof currencySymbol !== 'undefined' ? currencySymbol : "$";
	var tblRowUserdata	= "<tr style=\"font-size:30px;  text-align:right;\">" + "<td style=\" padding-left:10px; width:140px;\">" + convertToCurrencyFormat(stats.sum, currencySymbol) + ""+ "" + "<tr>" + "<td style=\"font-size:25px;padding-bottom:4px;\">"+"("+ stats.count +")"+ "" + "" +"<tr>" +"<td style=\"font-size:17px;  text-align:center;color:"+(((stats.variation).indexOf("-")!= -1)?"red":"green")+";\">" + stats.variation + "" + "<td>" + "" + "";
	$(tblRowUserdata).appendTo(userdata);
}
function addRankDetails(stats, userdata)
{
	var rank			= stats.rank;
	var rankVariation	= stats.rankVariation;
	var tblRowUserdata	= "<tr style=\"font-size:30px;  text-align:right; \">" + "<td style=\" padding-left:10px; width:80px;\">" + rank + ""+ "" +"<tr>" +"<td style=\"font-size:17px;  text-align:center; color:"+(((rankVariation).indexOf("-")!= -1)?"red":"green")+";\">" + rankVariation + "" + "<td>" + "" + "";
	$(tblRowUserdata).appendTo(userdata);
}
