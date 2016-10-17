object a1{

	def binarysearch(a:Array[Int],sno:Int,l:Int,r:Int):Int=
	{
		var mid=(l+r)/2
		println("in bs")
		if(l>r)
		{
			println("not found")
			return -1;
		}
		else if(a(mid)==sno)
		{
			println("found at "+(mid+1));
			return 1;
		}
		else if (a(mid)<sno)
		{
			println("num greater than mid "+(mid+1))
			binarysearch(a,sno,mid+1,r);
		}
		else{
			println("num smaller than mid "+(mid+1))
			binarysearch(a,sno,l,mid-1);
		}
	}

	def main(args:Array[String] )
	{

		var n=Console.readInt
		var a=new Array[Int](n)
		for ( i <- 0 to n-1)
		{
			a(i)=Console.readInt

		}

		println("Type number to search")
		var s=Console.readInt
		println(binarysearch(a,s,0,n-1))
		/*for (i <-0 to n-1 )
		{
			println (a(i))
		}
		*/
	}
}
