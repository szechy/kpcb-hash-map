require 'csv'

hackers = CSV.read('mhacks6.csv')

CSV.foreach('mhacks6.csv') do |row
	puts hackers.inspect
end