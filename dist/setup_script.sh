# Change
# cd python_files/arbitrary_style_transfer
# wget https://cmu.box.com/shared/static/diaquzqnmae38rjcqsqbqf45fe7ptuq6.zip 
# unzip diaquzqnmae38rjcqsqbqf45fe7ptuq6.zip
# rm  diaquzqnmae38rjcqsqbqf45fe7ptuq6.zip
# cd ../..

wget -c https://s3-us-west-2.amazonaws.com/wengaoye/vgg19_normalised.npz
mkdir python_files/arbitrary_style_transfer/data
mv vgg19_normalised.npz python_files/arbitrary_style_transfer/data
wget -c https://s3-us-west-2.amazonaws.com/wengaoye/arbitrary_style_model_style-weight-2e0.zip
unzip arbitrary_style_model_style-weight-2e0.zip 
mv models/checkpoint models/style_weight_2e0.ckpt
mv models/* python_files/arbitrary_style_transfer/data
rm arbitrary_style_model_style-weight-2e0.zip
rm -r models